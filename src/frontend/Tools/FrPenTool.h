#ifndef FR_PEN_TOOL
#define FR_PEN_TOOL

// includes
#include "FrTool.h"
#include "FrMacro.h"

// abstract class for all tools
// used by application
class FrPenTool : public FrTool {
public:
	virtual void Start();
	virtual void Stop();
    virtual bool OnMouseUp(FrInteractorStyle* is, FrMouseParams& params);
	virtual bool OnMouseDown(FrInteractorStyle* is, FrMouseParams& params);
	virtual bool OnMouseMove(FrInteractorStyle* is, FrMouseParams& params);
	virtual bool OnMouseDrag(FrInteractorStyle* is, FrMouseParams& params);

public:
	/// Default constructor
	FrPenTool();
	/// Destructor
	virtual ~FrPenTool();
};

#endif // FR_PEN_TOOL