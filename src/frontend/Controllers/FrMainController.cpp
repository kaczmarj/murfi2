#include "FrMainController.h"
#include "FrCommandController.h"
#include "FrMainWindow.h"
#include "FrMainDocument.h"
#include "FrToolController.h"
#include "FrInteractorStyle.h"
#include "FrBaseView.h"
#include "FrPanTool.h"
#include "FrZoomTool.h"
#include "FrCompositeTool.h"
#include "FrImageDocObj.h"
#include "QVTKWidget.h"

#include "vtkRenderWindowInteractor.h"

#include "Qt/QMessageBox.h"


// Implementation of FrMainController
FrMainController::FrMainController(FrMainWindow* view, FrMainDocument* doc)
    : m_MainView(view), m_MainDocument(doc), m_toolController(0){

    m_toolController = new FrToolController(this);

    FrCompositeTool* tool = new FrCompositeTool();
    tool->SetDocument(m_MainDocument);
    m_toolController->PushTool(tool);
}

FrMainController::~FrMainController(){
    if(m_toolController) delete m_toolController;
}

void FrMainController::Initialize(){
    
    // Initialize FrCommandController
    FrCommandController::Instance()->SetOwner(this);

    // Initialize view
    if(m_MainView){        
        m_MainView->SetMainController(this);
        m_MainView->SetMainDocument(m_MainDocument);
        m_MainView->Initialize();

        // Setup interactor style
        if(m_MainView->GetQVTKWidget()) {
            FrInteractorStyle* style = new FrInteractorStyle(this);
            m_MainView->GetQVTKWidget()->GetInteractor()->SetInteractorStyle(style);
        }
    }
    
    // Initialize document
    if(m_MainDocument){
        // TODO: Some initialization
        m_MainDocument->SetDefaultValues();

        FrSaveTabSettingsCmd* cmd = FrCommandController::CreateCmd<FrSaveTabSettingsCmd>();
        cmd->SetIsDefault(true);
        cmd->Execute();
        delete cmd;
    }
}

bool FrMainController::HasActiveTool(){
    bool result = false;
    if(m_toolController){
        result = (m_toolController->GetCurrentTool() != 0);
    }
    return result;
}

FrTool* FrMainController::GetCurrentTool(){
    FrTool* result = 0;
    if(m_toolController){
        result = m_toolController->GetCurrentTool();
    }
    return result;
}

#include <Qt/QString.h>
void FrMainController::LoadImage(QString& fileName){
        
    FrImageDocObj* imgObj = new FrImageDocObj();

    if(imgObj->LoadFromFile(fileName)){
        m_MainDocument->Add(imgObj);
    }
    else{
        // TODO: process error
    }    
    m_MainView->GetCurrentView()->UpdatePipeline(FRP_FULL);
}

void FrMainController::Notify(int notifyCode){
	// Do nothing here
}

void FrMainController::SaveCurrentViewToTab(){

    FrSaveTabSettingsCmd* cmd = FrCommandController::CreateCmd<FrSaveTabSettingsCmd>();
    cmd->Execute();
    delete cmd;
}

void FrMainController::ChangeView(int view){
    FrChangeViewCmd::View targetView = FrChangeViewCmd::Unknown;
    switch(view){
    case 0: targetView = FrChangeViewCmd::Slice;
        break;
    case 1: targetView = FrChangeViewCmd::Mosaic;
        break;
    case 2: targetView = FrChangeViewCmd::Ortho;
        break;
    }

    FrChangeViewCmd* cmd = FrCommandController::CreateCmd<FrChangeViewCmd>();
    cmd->SetTargetView(targetView);
    cmd->Execute();
    delete cmd;    
}

void FrMainController::ChangeBookmark(int id){
    // Create complex command and execute it
    FrUpdateTabsCmd* cmd1 = FrCommandController::CreateCmd<FrUpdateTabsCmd>();
    cmd1->SetAction(FrUpdateTabsCmd::SetCurrentTab);
    cmd1->SetTabSettingsDocObj(0L);
    cmd1->SetTabID( id );

    FrChangeViewCmd* cmd2 = FrCommandController::CreateCmd<FrChangeViewCmd>();
    cmd2->SetTargetView(FrChangeViewCmd::Synchronize);
        
    FrMultiCmd* cmd = FrCommandController::CreateCmd<FrMultiCmd>();
    cmd->AddCommand(cmd1);
    cmd->AddCommand(cmd2);
    cmd->Execute();

    delete cmd;
}

void FrMainController::DeleteBookmark(int id){
    FrDeleteTabSettingsCmd* cmd = FrCommandController::CreateCmd<FrDeleteTabSettingsCmd>();
    cmd->SetTabID(id);
    if(!cmd->Execute()){
        QMessageBox::critical(this->GetMainView(),
                              "Error Closing Tab",
                              "Can't close this tab...");
    }
    delete cmd;
}