/*!
 * \copyright Copyright (c) 2017 Governikus GmbH & Co. KG, Germany
 */

#pragma once

#include <QDesignerCustomWidgetInterface>

namespace governikus
{

class GeneralSettingsWidgetDesignerPlugin
	: public QObject
	, public QDesignerCustomWidgetInterface
{
	Q_OBJECT
	Q_INTERFACES(QDesignerCustomWidgetInterface)

	private:
		bool mInitialized;

	public:
		GeneralSettingsWidgetDesignerPlugin(QObject* pParent = nullptr);

		QWidget* createWidget(QWidget* pParent) override;
		QString domXml() const override;
		QString includeFile() const override;
		QString name() const override;
		QString group() const override;
		QString toolTip() const override;
		QString whatsThis() const override;
		bool isContainer() const override;
		bool isInitialized() const override;
		QIcon icon() const override;
		void initialize(QDesignerFormEditorInterface*) override;
};

}
