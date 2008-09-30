#ifndef FR_SLICE_VIEW
#define FR_SLICE_VIEW

class QWidget;
class vtkInteractorStyle;

class vtkRenderer;
class vtkImageViewer2;
class vtkImageActor;
class vtkTextActor;
class vtkOutlineFilter;
class vtkPolyDataMapper;
class vtkFollower;

class QVTKWidget;
class FrMainWindow;
class FrTBCFilter;
class FrMosaicFilter;	// test
class Fr2DSliceActor;
class FrDocumentReader;
class FrSliceExtractor;
class FrLayeredImage;	// test

#include "FrBaseView.h"

// Wrapper for QVTKWidget.
class FrSliceView : public FrBaseView
{ 
public:
    FrSliceView(FrMainWindow* mainWindow);
    virtual ~FrSliceView();

    virtual void Initialize();
    virtual void UpdatePipeline(int point);
    virtual void SetupRenderers();
    virtual void RemoveRenderers();

    FrSliceExtractor* GetSliceExtractor() { return m_SliceExtractor; }
    FrTBCFilter* GetTBCFilter() { return m_tbcFilter; }
    vtkRenderer* GetRenderer(){ return m_renderer; }
    

private:
    // Pipeline
    FrDocumentReader* m_docReader;
    FrSliceExtractor* m_SliceExtractor;
    FrTBCFilter* m_tbcFilter;
    vtkRenderer* m_renderer;

    // Actors
	Fr2DSliceActor* m_actor;
    vtkTextActor* m_tactor;

	// test
	FrLayeredImage* m_LayeredImage;

};

#endif

