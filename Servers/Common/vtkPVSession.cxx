/*=========================================================================

  Program:   ParaView
  Module:    $RCSfile$

  Copyright (c) Kitware, Inc.
  All rights reserved.
  See Copyright.txt or http://www.paraview.org/HTML/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#include "vtkPVSession.h"

#include "vtkObjectFactory.h"
#include "vtkPVProgressHandler.h"

//----------------------------------------------------------------------------
vtkPVSession::vtkPVSession()
{
  this->ProgressHandler = vtkPVProgressHandler::New();
  this->ProgressHandler->SetSession(this); // not reference counted.
  this->ProgressCount = 0;
}

//----------------------------------------------------------------------------
vtkPVSession::~vtkPVSession()
{
  this->ProgressHandler->SetSession(NULL);
  this->ProgressHandler->Delete();
  this->ProgressHandler = NULL;
}

//----------------------------------------------------------------------------
vtkPVSession::ServerFlags vtkPVSession::GetProcessRoles()
{
  return CLIENT_AND_SERVERS;
}

//----------------------------------------------------------------------------
vtkMultiProcessController* vtkPVSession::GetController(vtkPVSession::ServerFlags)
{
  return NULL;
}

//----------------------------------------------------------------------------
void vtkPVSession::PrepareProgress()
{
  if (this->ProgressCount == 0)
    {
    this->PrepareProgressInternal();
    }
  this->ProgressCount++;
}

//----------------------------------------------------------------------------
void vtkPVSession::CleanupPendingProgress()
{
  this->ProgressCount--;
  if (this->ProgressCount == 0)
    {
    this->CleanupPendingProgressInternal();
    }
  if (this->ProgressCount < 0)
    {
    vtkErrorMacro("PrepareProgress and CleanupPendingProgress mismatch!");
    this->ProgressCount = 0;
    }
}

//----------------------------------------------------------------------------
void vtkPVSession::PrepareProgressInternal()
{
  this->ProgressHandler->PrepareProgress();
}

//----------------------------------------------------------------------------
void vtkPVSession::CleanupPendingProgressInternal()
{
  this->ProgressHandler->CleanupPendingProgress();
}

//----------------------------------------------------------------------------
void vtkPVSession::PrintSelf(ostream& os, vtkIndent indent)
{
  this->Superclass::PrintSelf(os, indent);
}
