// $Id: IronFilterDTGeneratorMessenger.hh $
//
/// \file IronFilterDTGeneratorMessenger.hh
/// \brief Definition of the IronFilterDTGeneratorMessenger class

#ifndef IronFilterDTGeneratorMessenger_h
#define IronFilterDTGeneratorMessenger_h 1

#include "globals.hh"
#include "G4UImessenger.hh"
#include "G4UIdirectory.hh"
#include "G4UIcmdWithoutParameter.hh"
#include "G4UIcmdWithADouble.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWith3VectorAndUnit.hh"
#include "G4UIcmdWithABool.hh"

class IronFilterDTGeneratorAction;
class G4UIdirectory;

class G4UIcmdWithoutParameter;
class G4UIcmdWithAString;
class G4UIcmdWithADouble;
class G4UIcmdWithAnInteger;
class G4UIcmdWithADoubleAndUnit;
class G4UIcmdWith3VectorAndUnit;
class G4UIcmdWithABool;

class IronFilterDTGeneratorMessenger : public G4UImessenger {

public:

	IronFilterDTGeneratorMessenger(IronFilterDTGeneratorAction*);
	virtual ~IronFilterDTGeneratorMessenger();

	virtual void SetNewValue(G4UIcommand*, G4String);

private:

	IronFilterDTGeneratorAction* primaryGenerator;

	G4UIdirectory* primaryGeneratorDir;

	G4UIcmdWithAnInteger* cmdSetFileNumber;

  G4UIcmdWithAnInteger* cmdSetTotalEvent;

};

#endif
