#include "oauth2.h"
#include <QDebug>
#include <QApplication>
#include "logindialog.h"
#include <QSettings>
#include <QMessageBox>
#include <QNetworkRequest>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <qjson/parser.h>

OAuth2::OAuth2(QWidget* parent)
{
    //You need to login to Google, so first you need to create simple
    //Google account. Then you can visit the page
    //
    // https://code.google.com/apis/console
    //
    //there you can create your application. You need to check access to Calendar API.
    //
    //Then  you can see credentials of your application.
    //You need to copy and paste Client_ID and Redirect_URI to the strings below.
    //
    m_strEndPoint = "https://accounts.google.com/o/oauth2/auth";
    m_strScope = "https://www.googleapis.com/auth/calendar"; //Access to Calendar service
    m_strClientID = "269204810048.apps.googleusercontent.com";
    m_strRedirectURI = "urn:ietf:wg:oauth:2.0:oob";
    m_strResponseType = "code";

    m_pLoginDialog = new LoginDialog(parent);
    m_pParent = parent;
    connect(m_pLoginDialog, SIGNAL(accessTokenObtained()), this, SLOT(accessTokenObtained()));
}

void OAuth2::replyReadyRead()
{
    QByteArray response = m_networkReply->readAll();
    QString response_str = QString(response);
    qDebug() << "Obtained response = " << response_str;

    QJson::Parser parser;
    bool ok;

    QVariantMap result = parser.parse (response, &ok).toMap();
    if (!ok) {
       qDebug() << "Error while parsing JSON response from Google";
       return;
    }

    m_strAccessToken = result["access_token"].toString();

    QSettings settings("it.robol", "TimeTracker");
    settings.setValue("access_token", m_strAccessToken);
    m_pLoginDialog->setLoginUrl("");
    emit loginDone();
}

void OAuth2::accessTokenObtained()
{

    QNetworkRequest request(QUrl("https://accounts.google.com/o/oauth2/token"));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
    // request.setHeader("Host", "accounts.google.com");

    QByteArray data;
    QUrl params;

    params.addQueryItem("code", m_pLoginDialog->accessToken());
    params.addQueryItem("client_id", "269204810048.apps.googleusercontent.com");
    params.addQueryItem("client_secret", "XCsFiCzFxaudjU56S54pTKUN");
    params.addQueryItem("redirect_uri", "urn:ietf:wg:oauth:2.0:oob");
    params.addQueryItem("grant_type", "authorization_code");

    data = params.encodedQuery();

    qDebug() << "Preparing to send data = " << data;

    m_networkReply = m_networkAccessManager.post(request, data);
    connect (m_networkReply, SIGNAL(readyRead()), this, SLOT(replyReadyRead()));

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
    return m_strAccessToken;
}

bool OAuth2::isAuthorized()
{
    return m_strAccessToken != "";
}

void OAuth2::startLogin(bool bForce)
{
    qDebug() << "OAuth2::startLogin";
    QSettings settings("it.robol", "TimeTracker");
    QString str = settings.value("access_token", "").toString();

    qDebug() << "OAuth2::startLogin, token from Settings" << str;

    if(str.isEmpty() || bForce)
    {
        m_pLoginDialog->setLoginUrl(loginUrl());
        m_pLoginDialog->show();

    }
    else
    {
        m_strAccessToken = str;
        emit loginDone();
    }
}

