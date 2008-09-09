#ifndef FR_MAIN_WINDOW
#define FR_MAIN_WINDOW


#include "ui_FrMainWindow.h"

// Forward declaration
class QTabWidget;

class FrView2D;
class FrMainDocument;
class FrMainController;
class FrLowPanel;
class FrToolsPanel;
class FrBookmarkWidget;


class FrMainWindow: public QMainWindow, public Ui::MainWindow {
	Q_OBJECT
public:
	FrMainWindow();
    ~FrMainWindow();

    void SetDocument(FrMainDocument* value){ m_document = value; }
    FrMainDocument* GetDocument(){ return m_document; }

    void SetController(FrMainController* value){ m_controller = value; }
    FrMainController* GetController() { return m_controller; }

    FrView2D* GetView2D(){ return m_view2D; }

public slots:
	void brightnessValueChanged();
	void contrastValueChanged();
	void thresholdValueChanged();

	void tool1Triggered();
	void tool2Triggered();
	void tool3Triggered();
	void mode1Clicked();
	void mode2Clicked();
	void mode3Clicked();
	void tabChanged(int index);
	void bookmarkChanged(int index);
	void saveToTab();
    void openImage();

signals:


private:
    FrMainController* m_controller;
    FrMainDocument* m_document;
    FrView2D* m_view2D;

public:
    QTabWidget* m_tabWidget;
	QWidget*    m_slice2DWidget;
	QWidget*    m_graphWidget;

	FrToolsPanel*   m_toolsPanel;
	FrLowPanel*     m_lowPanel;
	FrBookmarkWidget* m_bookmarkWidget;
};

#endif