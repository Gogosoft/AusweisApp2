/*!
 * \brief Unit tests for \ref DidAuthenticateEAC1
 *
 * \copyright Copyright (c) 2015-2017 Governikus GmbH & Co. KG, Germany
 */

#include "paos/invoke/DidAuthenticateResponseEac1.h"

#include "asn1/CVCertificate.h"
#include "EstablishPACEChannel.h"
#include "TestFileHelper.h"

#include <QtTest>

using namespace governikus;

class test_DidAuthenticateResponseEAC1
	: public QObject
{
	Q_OBJECT

	QByteArray readFile(const QString& pFileName)
	{
		return TestFileHelper::readFile(QString(":/card/").append(pFileName));
	}


	private Q_SLOTS:
		void type()
		{
			DIDAuthenticateResponseEAC1 elem;
			elem.setMessageId("dummy");
			QCOMPARE(elem.mType, PaosType::DID_AUTHENTICATE_RESPONSE_EAC1);
		}


		void getCertificateHolderAuthorizationTemplate()
		{
			DIDAuthenticateResponseEAC1 msg;
			msg.setMessageId("dummy");
			msg.setCertificateHolderAuthorizationTemplate("dummy cert holder");
			QCOMPARE(msg.getCertificateHolderAuthorizationTemplate(), QByteArray("dummy cert holder"));
			QVERIFY(msg.marshall().contains("<CertificateHolderAuthorizationTemplate>dummy cert holder</CertificateHolderAuthorizationTemplate>"));
		}


		void getEFCardAccess()
		{
			DIDAuthenticateResponseEAC1 msg;
			msg.setMessageId("dummy");
			msg.setEFCardAccess("dummy card access");
			QCOMPARE(msg.getEFCardAccess(), QByteArray("dummy card access"));
			QVERIFY(msg.marshall().contains("<EFCardAccess>dummy card access</EFCardAccess>"));
		}


		void getIDPICC()
		{
			DIDAuthenticateResponseEAC1 msg;
			msg.setMessageId("dummy");
			msg.setIDPICC("bla bla bla");
			QCOMPARE(msg.getIDPICC(), QByteArray("bla bla bla"));
			QVERIFY(msg.marshall().contains("<IDPICC>bla bla bla</IDPICC>"));
		}


		void getChallenge()
		{
			DIDAuthenticateResponseEAC1 msg;
			msg.setMessageId("dummy");
			msg.setChallenge("1234567890");
			QVERIFY(msg.marshall().contains("<Challenge>1234567890</Challenge>"));
		}


		void certificationAuthorityReference()
		{
			const auto& cvca_DETESTeID00002 = CVCertificate::fromHex(readFile("cvca-DETESTeID00002.hex"));
			const auto& cvca_DETESTeID00001 = CVCertificate::fromHex(readFile("cvca-DETESTeID00001.hex"));

			EstablishPACEChannelOutput channel;
			channel.setCarCurr(cvca_DETESTeID00002->getBody().getCertificateHolderReference());
			channel.setCarPrev(cvca_DETESTeID00001->getBody().getCertificateHolderReference());

			DIDAuthenticateResponseEAC1 msg;
			msg.setMessageId("dummy");
			msg.setCertificationAuthorityReference(channel);
			QVERIFY(msg.marshall().contains("<CertificationAuthorityReference>DETESTeID00002</CertificationAuthorityReference>\n    <CertificationAuthorityReference>DETESTeID00001</CertificationAuthorityReference>"));
		}


};

QTEST_GUILESS_MAIN(test_DidAuthenticateResponseEAC1)
#include "test_DidAuthenticateResponseEAC1.moc"
