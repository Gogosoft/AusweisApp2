/*!
 * \brief Model implementation for the settings.
 *
 * \copyright Copyright (c) 2016-2017 Governikus GmbH & Co. KG, Germany
 */

#pragma once

#include <QObject>

namespace governikus
{

class SettingsModel
	: public QObject
{
	Q_OBJECT
	Q_PROPERTY(QString translationTrigger READ getEmptyString NOTIFY fireLanguageChanged)
	Q_PROPERTY(QString language READ getLanguage WRITE setLanguage NOTIFY fireLanguageChanged)
	Q_PROPERTY(bool developerMode READ isDeveloperMode WRITE setDeveloperMode NOTIFY fireDeveloperModeChanged)
	Q_PROPERTY(bool useSelfauthenticationTestUri READ useSelfauthenticationTestUri WRITE setUseSelfauthenticationTestUri NOTIFY fireUseSelfauthenticationTestUriChanged)
	Q_PROPERTY(bool pinPadMode READ getPinPadMode WRITE setPinPadMode NOTIFY firePinPadModeChanged)
	Q_PROPERTY(QString serverName READ getServerName WRITE setServerName NOTIFY fireDeviceNameChanged)

	public:
		SettingsModel();

		QString getEmptyString();
		QString getLanguage() const;
		void setLanguage(const QString& pLanguage);

		bool isDeveloperMode() const;
		void setDeveloperMode(bool pEnabled);

		bool useSelfauthenticationTestUri() const;
		void setUseSelfauthenticationTestUri(bool pUse);

		QString getServerName() const;
		Q_INVOKABLE bool isValidServerName(const QString& name) const;
		void setServerName(const QString& name);

		Q_INVOKABLE void removeTrustedCertificate(const QString& pFingerprint);

		bool getPinPadMode() const;
		void setPinPadMode(bool pPinPadMode);

	Q_SIGNALS:
		void fireLanguageChanged();
		void fireDeveloperModeChanged();
		void fireUseSelfauthenticationTestUriChanged();
		void fireDeviceNameChanged();
		void firePinPadModeChanged();
};

} /* namespace governikus */
