#include "vtkClientServerInterpreter.h"
#include "vtkClientServerStream.h"

extern void Vtkparaviewcswrapped_Initialize(vtkClientServerInterpreter*);

vtkClientServerID GetUniqueID()
{
  static vtkClientServerID id = {3};
  ++id.ID;
  return id;
}

// ClientServer wrapper initialization functions.
extern void vtkCommonCS_Initialize(vtkClientServerInterpreter*);
extern void vtkFilteringCS_Initialize(vtkClientServerInterpreter*);
extern void vtkImagingCS_Initialize(vtkClientServerInterpreter*);
extern void vtkGraphicsCS_Initialize(vtkClientServerInterpreter*);
extern void vtkIOCS_Initialize(vtkClientServerInterpreter*);
extern void vtkRenderingCS_Initialize(vtkClientServerInterpreter*);

int main()
{
  vtkClientServerInterpreter* interp = vtkClientServerInterpreter::New();
  interp->SetLogStream(&cout);

  vtkCommonCS_Initialize(interp);
  vtkFilteringCS_Initialize(interp);
  vtkImagingCS_Initialize(interp);
  vtkGraphicsCS_Initialize(interp);
  vtkIOCS_Initialize(interp);
  vtkRenderingCS_Initialize(interp);

  vtkClientServerStream css;

  vtkClientServerStream::Commands cnew = vtkClientServerStream::New;
  vtkClientServerStream::Commands invoke = vtkClientServerStream::Invoke;
  vtkClientServerStream::Types end = vtkClientServerStream::End;
  vtkClientServerStream::Types result = vtkClientServerStream::LastResult;
  vtkClientServerID renWin = GetUniqueID();
  vtkClientServerID ren1 = GetUniqueID();
  vtkClientServerID iren = GetUniqueID();
  vtkClientServerID sphere = GetUniqueID();
  vtkClientServerID mapper = GetUniqueID();
  vtkClientServerID actor = GetUniqueID();
  css << cnew << "vtkSphereSource" << sphere << end;
  css << cnew << "vtkActor" << actor << end;
  css << cnew << "vtkPolyDataMapper" << mapper << end;
  css << cnew << "vtkRenderer" << ren1 << end;
  css << cnew << "vtkRenderWindow" << renWin << end;
  css << cnew << "vtkRenderWindowInteractor" << iren << end;
  css << invoke << renWin << "AddRenderer" << ren1 << end;
  css << invoke << iren << "SetRenderWindow" << renWin << end;
  css << invoke << actor << "SetMapper" << mapper << end;
  css << invoke << sphere << "GetOutput" << end;
  css << invoke << mapper << "SetInput" << result << end;
  css << invoke << ren1 << "AddActor" << actor << end;
  css << invoke << ren1 << "Render" << end;
  css << invoke << iren << "Initialize" << end;
  css << invoke << iren << "Start" << end;

  interp->ProcessStream(css);

  interp->Delete();
  return 0;
}
