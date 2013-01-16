#include "oauth2.h"
#include <QDebug>
#include <QApplication>
#include "logindialog.h"
#include <QSettings>
#include <QMessageBox>
#include <QNetworkRequest>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QDateTime>
#include <qjson/parser.h>

OAuth2::OAuth2(QWidget* parent)
{
    connect (&m_networkAccessManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(analyzeReply(QNetworkReply*)));

    m_strEndPoint = "https://accounts.google.com/o/oauth2/auth";
    m_strScope = "https://www.googleapis.com/auth/calendar"; //Access to Calendar service
    m_strClientID = "269204810048.apps.googleusercontent.com";
    m_strRedirectURI = "urn:ietf:wg:oauth:2.0:oob";
    m_strResponseType = "code";

    m_pLoginDialog = new LoginDialog(parent);
    m_pParent = parent;
    connect(m_pLoginDialog, SIGNAL(accessTokenObtained()), this, SLOT(authorizationTokenObtained()));
}

void
OAuth2::analyzeReply(QNetworkReply *reply)
{
    QByteArray response = reply->readAll();
    QJson::Parser parser;
    bool ok;

    qDebug() << "Reply received, starting to parse";
    qDebug() << "Response: " << QString(response);

    QVariantMap result = parser.parse(response, &ok).toMap();

    if (!ok)
    {
        qDebug() << "Error while parsing the response from Google";
        qDebug() << "Response obtained:" << QString(response);
    }

    // Check for an access token in the response. If that is present, load
    // it with the associated expire date.
    if (result.contains("access_token"))
    {
        setAccessToken(result["access_token"].toString(),
                       QDateTime::currentDateTimeUtc().addSecs(result["expires_in"].toInt()));
    }

    // Check if we are also given a refresh token that can be used to refresh
    // this one when expires.
    if (result.contains("refresh_token"))
    {
        qDebug() << "Saving refresh token =" << result["refresh_token"].toString();
        m_refreshToken = result["refresh_token"].toString();
    }

    // Schedule the QNetworkReply for deletion as soon as possible.
    reply->deleteLater();
}

void OAuth2::setAccessToken(QString accessToken, QDateTime expireDate)
{
    qDebug() << "Registering a new access token =" << accessToken;
    qDebug() << "The token will expire on" << expireDate;

    m_accessToken = accessToken;
    m_accessTokenExpireDate = expireDate;

    // Save the token and the expire date in the settings.
    QSettings settings(OAUTH2_ORGANIZATION, OAUTH2_APPLICATION);
    settings.setValue("accessToken", accessToken);
    settings.setValue("accessTokenExpireDate", expireDate);

    // Complete the login process, if any
    m_pLoginDialog->setLoginUrl("");

    emit loginDone();
}

void OAuth2::authorizationTokenObtained()
{
    // Get the authorization token and use it as a refresh token.
    requestAccessToken(m_pLoginDialog->authorizationToken());
}

void OAuth2::requestAccessToken(QString authorizationToken)
{
    QNetworkRequest request(QUrl(m_strEndPoint));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    QUrl params;

    params.addQueryItem("code", authorizationToken);
    params.addQueryItem("client_id", m_strClientID);
    params.addQueryItem("client_secret", "XCsFiCzFxaudjU56S54pTKUN");
    params.addQueryItem("redirect_uri", "urn:ietf:wg:oauth:2.0:oob");
    params.addQueryItem("grant_type", "authorization_code");

    m_networkAccessManager.post(request, params.encodedQuery());
}

void
OAuth2::retrieveAccessToken()
{
    QSettings settings(OAUTH2_ORGANIZATION, OAUTH2_APPLICATION);

    // Check if the current stored access token is valid. If that's
    // the case, there is no need to do anything.
    QDateTime m_accessTokenExpireDate = settings.value("accessTokenExpireDate").toDateTime();
    if (QDateTime::currentDateTimeUtc() < m_accessTokenExpireDate)
    {
        qDebug() << "Found a valid token in the settings, using it";
        setAccessToken(settings.value("accessToken").toString(), m_accessTokenExpireDate);
        return;
    }

    if (settings.contains("refresh_token") && !settings.value("refresh_token").toString().isEmpty())
    {
        qDebug() << "Trying to refresh the token";
        m_refreshToken = settings.value("refresh_token", "").toString();

        // Perform the actual refresh of the token
        QNetworkRequest request(QUrl(m_strEndPoint));
        request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

        QUrl params;
        params.addQueryItem("client_id", m_strClientID);
        params.addQueryItem("client_secret", "XCsFiCzFxaudjU56S54pTKUN");
        params.addQueryItem("refresh_token", m_refreshToken);
        params.addQueryItem("grant_type", "refresh_token");

        qDebug() << "Query = " << params.encodedQuery();

        m_networkAccessManager.post(request, params.encodedQuery());
    }
    else
    {
        // Show the login dialog so that the user can authorize the application
        // to handle his data.
        m_pLoginDialog->setLoginUrl(loginUrl());
        m_pLoginDialog->show();
    }
}

QString OAuth2::loginUrl()
{
    QString str = QString("%1?client_id=%2&redirect_uri=%3&response_type=%4&scope=%5").arg(m_strEndPoint).arg(m_strClientID).
            arg(m_strRedirectURI).arg(m_strResponseType).arg(m_strScope);
    qDebug() << "Login URL" << str;
    return str;
}

QString OAuth2::accessToken()
{
    if (QDateTime::currentDateTimeUtc() < m_accessTokenExpireDate)
        return m_accessToken;
    else
    {
        qDebug() << "The token has expired";
        m_accessToken = "";

        // Try to refresh the token using a refresh token, if it does exists,
        // or by retriggering the authentication process if it does not.
        retrieveAccessToken();
    }
}

bool OAuth2::isAuthorized()
{
    return m_accessToken != "";
}

void OAuth2::startLogin(bool bForce)
{
    retrieveAccessToken();
}

