#ifndef OAUTH2_H
#define OAUTH2_H

#include <QString>
#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QDateTime>

#define OAUTH2_ORGANIZATION "it.robol"
#define OAUTH2_APPLICATION  "TimeTracker"

class LoginDialog;

class OAuth2 : public QObject
{
    Q_OBJECT

public:
    OAuth2(QWidget* parent = 0);
    QString accessToken();
    bool isAuthorized();
    void startLogin(bool bForce);

    QString loginUrl();

signals:
    void loginDone();

private slots:
    void analyzeReply(QNetworkReply *reply);
    void authorizationTokenObtained();

private:

    /**
     * @brief retrieveAccessToken is used to retrieve a new access token based on
     * a previously obtained refresh_token, or on the base authorizationToken.
     */
    void retrieveAccessToken();

    /**
     * @brief setAccessToken select the current valid access token that can be used
     * to interact with the OAuth 2.0 provider.
     * @param accessToken is a string representing the access token.
     * @param expireDate is the expire date of the token.
     * @param refreshToken is the refresh token obtained by the server. If this string
     * is empty the older one won't be overwritten.
     */
    void setAccessToken(QString accessToken, QDateTime expireDate, QString refreshToken);

    /**
     * @brief requestAccessToken asks the OAuth 2.0 server for an access token
     * using the given authorizationToken.
     * @param authorizationToken obtained by permission of the user using the loginDialog.
     */
    void requestAccessToken(QString authorizationToken);

    /**
     * @brief requestAccessToken asks the OAuth 2.0 server for an access token
     * using the stored refreshToken in the settings. If the calls fails
     * this use the fallback case of requestAccessToken();
     */
    void refreshAccessToken();

    QNetworkAccessManager m_networkAccessManager;

    QString m_strEndPoint;
    QString m_strScope;
    QString m_strClientID;
    QString m_strRedirectURI;
    QString m_strResponseType;

    LoginDialog* m_pLoginDialog;
    QWidget* m_pParent;
};

#endif // OAUTH2_H
