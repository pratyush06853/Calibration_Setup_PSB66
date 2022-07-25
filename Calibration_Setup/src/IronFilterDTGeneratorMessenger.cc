// $Id: IronFilterDTGeneratorMessenger.cc $
//
/// \file IronFilterDTGeneratorMessenger.cc
/// \brief Definition of the IronFilterDTGeneratorMessenger class

#include "IronFilterDTGeneratorMessenger.hh"
#include "G4UIcmdWithAnInteger.hh"
#include "IronFilterDTGeneratorAction.hh"

IronFilterDTGeneratorMessenger::IronFilterDTGeneratorMessenger( IronFilterDTGeneratorAction* generator )  : G4UImessenger(), primaryGenerator(generator), primaryGeneratorDir(0) {

	  primaryGeneratorDir = new G4UIdirectory("/IronFilterDTGenerator/");
	  primaryGeneratorDir->SetGuidance("Generator controls TotalEvent and FileNumber");

    cmdSetFileNumber = new G4UIcmdWithAnInteger("/IronFilterDTGenerator/FileNumber", this);
    cmdSetFileNumber->SetGuidance("Set the ROOT file from which to sample position, direction and energy.");
    cmdSetFileNumber->SetParameterName("foo.root", false);
    cmdSetFileNumber->AvailableForStates(G4State_PreInit, G4State_Idle);

		cmdSetTotalEvent = new G4UIcmdWithAnInteger("/IronFilterDTGenerator/TotalEvent", this);
		cmdSetTotalEvent->SetGuidance("Set the name of the TotalEvent.");
		cmdSetTotalEvent->SetParameterName("geantino", false);
		cmdSetTotalEvent->AvailableForStates(G4State_PreInit, G4State_Idle);

}


IronFilterDTGeneratorMessenger::~IronFilterDTGeneratorMessenger(){

    delete cmdSetFileNumber;
		delete cmdSetTotalEvent;
}


void IronFilterDTGeneratorMessenger::SetNewValue(G4UIcommand* command, G4String newValue){

	if( command == cmdSetFileNumber )	{
		primaryGenerator->SetFileNumber( cmdSetFileNumber->GetNewIntValue(newValue));
		}

	if( command == cmdSetTotalEvent){
			primaryGenerator->SetTotalEvent( cmdSetFileNumber->GetNewIntValue(newValue));
		}
}
