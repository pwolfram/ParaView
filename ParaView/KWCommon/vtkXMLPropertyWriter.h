/*=========================================================================

  Program:   Visualization Toolkit
  Module:    vtkXMLPropertyWriter.h
  Language:  C++
  Date:      $Date$
  Version:   $Revision$

Copyright (c) 2000-2001 Kitware Inc. 469 Clifton Corporate Parkway,
Clifton Park, NY, 12065, USA.
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

 * Redistributions of source code must retain the above copyright notice,
   this list of conditions and the following disclaimer.

 * Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution.

 * Neither the name of Kitware nor the names of any contributors may be used
   to endorse or promote products derived from this software without specific 
   prior written permission.

 * Modified source versions must be plainly marked as such, and must not be
   misrepresented as being the original software.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS ``AS IS''
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHORS OR CONTRIBUTORS BE LIABLE FOR
ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

=========================================================================*/
// .NAME vtkXMLPropertyWriter - vtkProperty XML Writer.
// .SECTION Description
// vtkXMLPropertyWriter provides XML writing functionality to 
// vtkProperty.

#ifndef __vtkXMLPropertyWriter_h
#define __vtkXMLPropertyWriter_h

#include "vtkObject.h"

class vtkProperty;

class VTK_EXPORT vtkXMLPropertyWriter : public vtkObject
{
public:
  static vtkXMLPropertyWriter* New();
  vtkTypeRevisionMacro(vtkXMLPropertyWriter,vtkObject);
  void PrintSelf(ostream& os, vtkIndent indent);
  
  // Description:
  // Get/Set the Property to serialize.
  virtual void SetProperty(vtkProperty*);
  vtkGetObjectMacro(Property, vtkProperty);

  // Description:
  // Write a serialized representation of the Property
  virtual int Write(ostream &os, vtkIndent indent);

protected:
  vtkXMLPropertyWriter();
  ~vtkXMLPropertyWriter();  
  
  vtkProperty *Property;

private:
  vtkXMLPropertyWriter(const vtkXMLPropertyWriter&);  // Not implemented.
  void operator=(const vtkXMLPropertyWriter&);  // Not implemented.
};

#endif
