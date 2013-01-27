#include "oauth2.h"
#include <QDebug>
#include <QApplication>
#include "logindialog.h"
#include <QMessageBox>
#include <QNetworkRequest>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QDateTime>
#include <qjson/parser.h>
#include "settings.h"

OAuth2::OAuth2(QObject* parent)
{
    connect (&m_networkAccessManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(analyzeReply(QNetworkReply*)));

    m_strEndPoint = "https://accounts.google.com/o/oauth2/auth";
    m_strScope = "https://www.googleapis.com/auth/calendar"; //Access to Calendar service
    m_strClientID = "269204810048.apps.googleusercontent.com";
    m_strRedirectURI = "urn:ietf:wg:oauth:2.0:oob";
    m_strResponseType = "code";

    // m_pLoginDialog = new LoginDialog(parent);
    // connect(m_pLoginDialog, SIGNAL(accessTokenObtained()), this, SLOT(authorizationTokenObtained()));
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
    // it with the associated expire date. If a refresh token was present
    // store also that.
    if (result.contains("access_token"))
    {
        QString refreshToken = "";

        if (result.contains("refresh_token"))
            refreshToken = result["refresh_token"].toString();

        setAccessToken(result["access_token"].toString(),
                       QDateTime::currentDateTimeUtc().addSecs(result["expires_in"].toInt()),
                       refreshToken);
    }

    // Schedule the QNetworkReply for deletion as soon as possible.
    reply->deleteLater();
}

void OAuth2::setAccessToken(QString accessToken, QDateTime expireDate, QString refreshToken)
{
    qDebug() << "Registering a new access token:" << accessToken;
    qDebug() << "The token will expire on" << expireDate;

    // Save the token and the expire date in the settings.
    Settings settings;
    settings.setValue("accessToken", accessToken);
    settings.setValue("accessTokenExpireDate", expireDate);

    if (!refreshToken.isEmpty())
        settings.setValue("refreshToken", refreshToken);

    // Complete the login process, if any
    // m_pLoginDialog->setLoginUrl("");

    emit loginDone();
}

void OAuth2::authorizationTokenObtained(QString authorizationToken)
{
    // Get the authorization token and use it as a refresh token.
    requestAccessToken(authorizationToken);
}

void OAuth2::requestAccessToken(QString authorizationToken)
{
    QNetworkRequest request(QUrl("https://accounts.google.com/o/oauth2/token"));
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
    Settings settings;

    // Dump the content of the settings so we can debug what's
    // really happening.
    qDebug() << "accessTokenExpireDate:" << settings.value("accessTokenExpireDate");
    qDebug() << "accessToken" << settings.value("accessToken");
    qDebug() << "refreshToken" << settings.value("refreshToken");

    if (!settings.value("refreshToken", "").toString().isEmpty())
    {
        qDebug() << "Trying to refresh the token";
        QString currentRefreshToken = settings.value("refreshToken", "").toString();

        // Perform the actual refresh of the token
        QNetworkRequest request(QUrl("https://accounts.google.com/o/oauth2/token"));
        request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

        QUrl params;
        params.addQueryItem("client_id", m_strClientID);
        params.addQueryItem("client_secret", "XCsFiCzFxaudjU56S54pTKUN");
        params.addQueryItem("refresh_token", currentRefreshToken);
        params.addQueryItem("grant_type", "refresh_token");

        qDebug() << "Query = " << params.encodedQuery();

        m_networkAccessManager.post(request, params.encodedQuery());
    }
    else
    {
        // Show the login dialog so that the user can authorize the application
        // to handle his data.
        qDebug() << "Asking the application to provide a login handler";
        emit loginHandlerRequired(QUrl(loginUrl()));
//        m_pLoginDialog->setLoginUrl(loginUrl());
//        m_pLoginDialog->show();
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
    Settings settings;
    QDateTime expireDate = settings.value("accessTokenExpireDate").toDateTime();

    if (QDateTime::currentDateTimeUtc() >= expireDate)
    {
        qDebug() << "The token has expired";
        settings.setValue("accessToken", "");

        // Try to refresh the token using a refresh token, if it does exists,
        // or by retriggering the authentication process if it does not.
        retrieveAccessToken();
    }

    return settings.value("accessToken").toString();
}

void OAuth2::clearToken()
{
    Settings settings;

    settings.setValue("accessToken", "");
    settings.setValue("accessTokenExpireDate", "");
    settings.setValue("refreshToken", "");
}

bool OAuth2::isAuthorized()
{
    Settings settings;
    return !settings.value("accessToken").toString().isEmpty() &&
            (QDateTime::currentDateTimeUtc() < settings.value("accessTokenExpireDate").toDateTime());
}

void OAuth2::startLogin(bool bForce)
{
    retrieveAccessToken();
}

