//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
// $Id: IronFilterActionInitialization.cc $
//
/// \file IronFilterActionInitialization.cc
/// \brief Implementation of the IronFilterActionInitialization class

#include "IronFilterActionInitialization.hh"
//#include "IronFilterPrimaryGeneratorAction.hh"
#include "IronFilterGPSGeneratorAction.hh"
//#include "IronFilterParticleGunAction.hh"
#include "IronFilterDTGeneratorAction.hh"
#include "IronFilterRunAction.hh"
#include "IronFilterEventAction.hh"
#include "IronFilterSteppingAction.hh"
#include "IronFilterDetectorConstruction.hh"
#include "IronFilterTrackingAction.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

IronFilterActionInitialization::IronFilterActionInitialization
							(IronFilterDetectorConstruction* detConstruction)
 : G4VUserActionInitialization(),
 fDetConstruction(detConstruction)
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

IronFilterActionInitialization::~IronFilterActionInitialization()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void IronFilterActionInitialization::BuildForMaster() const
{
  SetUserAction(new IronFilterRunAction);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void IronFilterActionInitialization::Build() const
{
  //SetUserAction(new IronFilterPrimaryGeneratorAction);
  SetUserAction(new IronFilterDTGeneratorAction);
  //SetUserAction(new IronFilterGPSGeneratorAction);
	//SetUserAction(new IronFilterParticleGunAction);
  SetUserAction(new IronFilterRunAction);
  //IronFilterEventAction* eventAction = new IronFilterEventAction;
  //SetUserAction(eventAction);
  SetUserAction(new IronFilterEventAction(runAction));
  SetUserAction(new IronFilterTrackingAction(eventAction));
  SetUserAction(new IronFilterSteppingAction(fDetConstruction, eventAction));
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
