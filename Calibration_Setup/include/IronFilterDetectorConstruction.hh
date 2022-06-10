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
// $Id: IronFilterDetectorConstruction.hh $
//
/// \file IronFilterDetectorConstruction.hh
/// \brief Definition of the IronFilterDetectorConstruction class

#ifndef IronFilterDetectorConstruction_h
#define IronFilterDetectorConstruction_h 1

#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"
#include "G4RotationMatrix.hh"

class G4VPhysicalVolume;
class IronFilterDetectorMessenger;//pratyush

class IronFilterDetectorConstruction : public G4VUserDetectorConstruction
{
  public:
    IronFilterDetectorConstruction();
    virtual ~IronFilterDetectorConstruction();

  public:
    virtual G4VPhysicalVolume* Construct();

    // get methods
    //
    ////const G4VPhysicalVolume* GetairlayersolidPV() const;
    ////const G4VPhysicalVolume* GetroomsolidPV() const;

    //lab
    const G4VPhysicalVolume* GetLabFloorWallsolidPV() const;
    const G4VPhysicalVolume* GetLabFloorExtendedsolidPV() const;
    const G4VPhysicalVolume* GetfrontglassdoorPV() const;
    const G4VPhysicalVolume* GetfrontdoorPV() const;
    const G4VPhysicalVolume* GetglasswindowPV() const;
    const G4VPhysicalVolume* GetreardoorPV() const;
    const G4VPhysicalVolume* GetInsulationPV() const;


    //fridge
    const G4VPhysicalVolume* GetDilutionUnitPV() const;
    const G4VPhysicalVolume* GetMixingPlatePV() const;
    const G4VPhysicalVolume* GetColdPlate2PV() const;
    const G4VPhysicalVolume* GetColdPlate1PV() const;
    const G4VPhysicalVolume* GetOneKPlatePV() const;
    const G4VPhysicalVolume* GetOneKShieldPV() const;
    const G4VPhysicalVolume* GetDilutionChamberPV() const;
    const G4VPhysicalVolume* GetFourKPlatePV() const;
    const G4VPhysicalVolume* GetFourKShieldPV() const;
    const G4VPhysicalVolume* GetSeventyKPlatePV() const;
    const G4VPhysicalVolume* GetSeventyKShieldPV() const;
    const G4VPhysicalVolume* GetOVCShieldPV() const;
    const G4VPhysicalVolume* GetBucketShieldingLeadPV() const;

    //1st Detector type A
    const G4VPhysicalVolume* GetshieldingleadPV2() const;
    const G4VPhysicalVolume* GetfilteraluminumPV2() const;
    //const G4VPhysicalVolume* GetmoderatorironPV2() const;
    const G4VPhysicalVolume* GetshieldcapironPV2() const;
    const G4VPhysicalVolume* GetinnershieldPV2() const;
    const G4VPhysicalVolume* GetDTsolidPV2() const;
    const G4VPhysicalVolume* GetIronsolidPV2() const;


    //2nd Detector type A
    const G4VPhysicalVolume* GetshieldingleadPV() const;
    const G4VPhysicalVolume* GetfilteraluminumPV() const;
    //const G4VPhysicalVolume* GetmoderatorironPV() const;
    const G4VPhysicalVolume* GetshieldcapironPV() const;
    const G4VPhysicalVolume* GetinnershieldPV() const;
    const G4VPhysicalVolume* GetDTsolidPV() const;
    const G4VPhysicalVolume* GetIronsolidPV() const;

    //3rd Detector type A
    const G4VPhysicalVolume* GetshieldingleadPV3() const;
    const G4VPhysicalVolume* GetfilteraluminumPV3() const;
    //const G4VPhysicalVolume* GetmoderatorironPV3() const;
    const G4VPhysicalVolume* GetshieldcapironPV3() const;
    const G4VPhysicalVolume* GetinnershieldPV3() const;
    const G4VPhysicalVolume* GetDTsolidPV3() const;
    const G4VPhysicalVolume* GetIronsolidPV3() const;

    //4th Detector type B
    const G4VPhysicalVolume* GetshieldingleadPV1() const;
    const G4VPhysicalVolume* GetfilteraluminumPV1() const;
    //const G4VPhysicalVolume* GetmoderatorironPV1() const;
    const G4VPhysicalVolume* GetshieldcapironPV1() const;
    const G4VPhysicalVolume* GetDTsolidPV1() const;
    const G4VPhysicalVolume* GetIronsolidPV1() const;

    //5th Detector type B
    const G4VPhysicalVolume* GetshieldingleadPV1_5() const;
    const G4VPhysicalVolume* GetfilteraluminumPV1_5() const;
    //const G4VPhysicalVolume* GetmoderatorironPV1_5() const;
    const G4VPhysicalVolume* GetshieldcapironPV1_5() const;
    const G4VPhysicalVolume* GetDTsolidPV1_5() const;
    const G4VPhysicalVolume* GetIronsolidPV1_5() const;

    //6th Detector type B
    const G4VPhysicalVolume* GetshieldingleadPV1_6() const;
    const G4VPhysicalVolume* GetfilteraluminumPV1_6() const;
    //const G4VPhysicalVolume* GetmoderatorironPV1_6() const;
    const G4VPhysicalVolume* GetshieldcapironPV1_6() const;
    const G4VPhysicalVolume* GetDTsolidPV1_6() const;
    const G4VPhysicalVolume* GetIronsolidPV1_6() const;




  private:
    // methods
    //
    void DefineMaterials();
    G4VPhysicalVolume* DefineVolumes();
    ////G4VPhysicalVolume* airlayer_solid_PV;
    ////G4VPhysicalVolume* room_solid_PV;

    //lab
    G4VPhysicalVolume* LabFloorWall_solid_PV;
    G4VPhysicalVolume* LabFloorExtended_solid_PV;
    G4VPhysicalVolume* frontglassdoor_PV;
    G4VPhysicalVolume* frontdoor_PV;
    G4VPhysicalVolume* glasswindow_PV;
    G4VPhysicalVolume* reardoor_PV;
    G4VPhysicalVolume* Insulation_PV;

    //fridge
    G4VPhysicalVolume* DilutionUnit_PV;
    G4VPhysicalVolume* MixingPlate_PV;
    G4VPhysicalVolume* ColdPlate2_PV;
    G4VPhysicalVolume* ColdPlate1_PV;
    G4VPhysicalVolume* OneKPlate_PV;
    G4VPhysicalVolume* OneKShield_PV;
    G4VPhysicalVolume* DilutionChamber_PV;
    G4VPhysicalVolume* FourKPlate_PV;
    G4VPhysicalVolume* FourKShield_PV;
    G4VPhysicalVolume* SeventyKPlate_PV;
    G4VPhysicalVolume* SeventyKShield_PV;
    G4VPhysicalVolume* OVCShield_PV;
    G4VPhysicalVolume* BucketShielding_Lead_PV;

    //1st Detector type A
    G4VPhysicalVolume* shielding_lead_PV_2;
    G4VPhysicalVolume* filter_aluminum_PV_2;
    //G4VPhysicalVolume* moderator_iron_PV_2;
    G4VPhysicalVolume* shield_cap_iron_PV_2;
    G4VPhysicalVolume* inner_shield_PV_2;
    G4VPhysicalVolume* DT_solid_PV_2;
    G4VPhysicalVolume* Iron_solid_PV_2;

    //2nd Detector type A
    G4VPhysicalVolume* shielding_lead_PV;
    G4VPhysicalVolume* filter_aluminum_PV;
    //G4VPhysicalVolume* moderator_iron_PV;
    G4VPhysicalVolume* shield_cap_iron_PV;
    G4VPhysicalVolume* inner_shield_PV;
    G4VPhysicalVolume* DT_solid_PV;
    G4VPhysicalVolume* Iron_solid_PV;

    //3rd Detector type A
    G4VPhysicalVolume* shielding_lead_PV_3;
    G4VPhysicalVolume* filter_aluminum_PV_3;
    //G4VPhysicalVolume* moderator_iron_PV_3;
    G4VPhysicalVolume* shield_cap_iron_PV_3;
    G4VPhysicalVolume* inner_shield_PV_3;
    G4VPhysicalVolume* DT_solid_PV_3;
    G4VPhysicalVolume* Iron_solid_PV_3;

    //4th Detector type B
    G4VPhysicalVolume* shielding_lead_PV_1;
    G4VPhysicalVolume* filter_aluminum_PV_1;
    //G4VPhysicalVolume* moderator_iron_PV_1;
    G4VPhysicalVolume* shield_cap_iron_PV_1;
    G4VPhysicalVolume* DT_solid_PV_1;
    G4VPhysicalVolume* Iron_solid_PV_1;

    //5th Detector type B
    G4VPhysicalVolume* shielding_lead_PV_1_5;
    G4VPhysicalVolume* filter_aluminum_PV_1_5;
    //G4VPhysicalVolume* moderator_iron_PV_1_5;
    G4VPhysicalVolume* shield_cap_iron_PV_1_5;
    G4VPhysicalVolume* DT_solid_PV_1_5;
    G4VPhysicalVolume* Iron_solid_PV_1_5;

    //6th Detector type B
    G4VPhysicalVolume* shielding_lead_PV_1_6;
    G4VPhysicalVolume* filter_aluminum_PV_1_6;
    //G4VPhysicalVolume* moderator_iron_PV_1_6;
    G4VPhysicalVolume* shield_cap_iron_PV_1_6;
    G4VPhysicalVolume* DT_solid_PV_1_6;
    G4VPhysicalVolume* Iron_solid_PV_1_6;



    G4bool  fCheckOverlaps; // option to activate checking of volumes overlaps
};

//// inline functions

////inline const G4VPhysicalVolume* IronFilterDetectorConstruction::GetairlayersolidPV() const {
////  return airlayer_solid_PV;
////}

////inline const G4VPhysicalVolume* IronFilterDetectorConstruction::GetroomsolidPV() const {
////  return room_solid_PV;
////}


//1st Detector type A

inline const G4VPhysicalVolume* IronFilterDetectorConstruction::GetshieldingleadPV2() const {
  return shielding_lead_PV_2;
}

//inline const G4VPhysicalVolume* IronFilterDetectorConstruction::GetmoderatorironPV2() const {
// return moderator_iron_PV_2;
//}

inline const G4VPhysicalVolume* IronFilterDetectorConstruction::GetfilteraluminumPV2() const {
  return filter_aluminum_PV_2;
}

inline const G4VPhysicalVolume* IronFilterDetectorConstruction::GetshieldcapironPV2() const {
  return shield_cap_iron_PV_2;
}

inline const G4VPhysicalVolume* IronFilterDetectorConstruction::GetDTsolidPV2() const {
  return DT_solid_PV_2;
}

inline const G4VPhysicalVolume* IronFilterDetectorConstruction::GetIronsolidPV2() const {
  return Iron_solid_PV_2;
}

//2nd Detector type A
inline const G4VPhysicalVolume* IronFilterDetectorConstruction::GetshieldingleadPV() const {
  return shielding_lead_PV;
}

inline const G4VPhysicalVolume* IronFilterDetectorConstruction::GetfilteraluminumPV() const {
  return filter_aluminum_PV;
}

//inline const G4VPhysicalVolume* IronFilterDetectorConstruction::GetmoderatorironPV() const {
// return moderator_iron_PV;
//}

inline const G4VPhysicalVolume* IronFilterDetectorConstruction::GetshieldcapironPV() const {
  return shield_cap_iron_PV;
}

inline const G4VPhysicalVolume* IronFilterDetectorConstruction::GetinnershieldPV() const {
  return inner_shield_PV;
}

inline const G4VPhysicalVolume* IronFilterDetectorConstruction::GetDTsolidPV() const {
  return DT_solid_PV;
}

inline const G4VPhysicalVolume* IronFilterDetectorConstruction::GetIronsolidPV() const {
  return Iron_solid_PV;
}

//3rd Detector type A

inline const G4VPhysicalVolume* IronFilterDetectorConstruction::GetshieldingleadPV3() const {
  return shielding_lead_PV_3;
}

//inline const G4VPhysicalVolume* IronFilterDetectorConstruction::GetmoderatorironPV3() const {
// return moderator_iron_PV_3;
//}

inline const G4VPhysicalVolume* IronFilterDetectorConstruction::GetfilteraluminumPV3() const {
  return filter_aluminum_PV_3;
}

inline const G4VPhysicalVolume* IronFilterDetectorConstruction::GetshieldcapironPV3() const {
  return shield_cap_iron_PV_3;
}

inline const G4VPhysicalVolume* IronFilterDetectorConstruction::GetDTsolidPV3() const {
  return DT_solid_PV_3;
}

inline const G4VPhysicalVolume* IronFilterDetectorConstruction::GetIronsolidPV3() const {
  return Iron_solid_PV_3;
}

//4th Detector type B

inline const G4VPhysicalVolume* IronFilterDetectorConstruction::GetshieldingleadPV1() const {
  return shielding_lead_PV_1;
}

//inline const G4VPhysicalVolume* IronFilterDetectorConstruction::GetmoderatorironPV1() const {
// return moderator_iron_PV_1;
//}

inline const G4VPhysicalVolume* IronFilterDetectorConstruction::GetfilteraluminumPV1() const {
  return filter_aluminum_PV_1;
}


inline const G4VPhysicalVolume* IronFilterDetectorConstruction::GetshieldcapironPV1() const {
  return shield_cap_iron_PV_1;
}


inline const G4VPhysicalVolume* IronFilterDetectorConstruction::GetDTsolidPV1() const {
  return DT_solid_PV_1;
}



inline const G4VPhysicalVolume* IronFilterDetectorConstruction::GetIronsolidPV1() const {
  return Iron_solid_PV_1;
}

//5th Detector type B

inline const G4VPhysicalVolume* IronFilterDetectorConstruction::GetshieldingleadPV1_5() const {
  return shielding_lead_PV_1_5;
}

//inline const G4VPhysicalVolume* IronFilterDetectorConstruction::GetmoderatorironPV1_5() const {
// return moderator_iron_PV_1_5;
//}

inline const G4VPhysicalVolume* IronFilterDetectorConstruction::GetfilteraluminumPV1_5() const {
  return filter_aluminum_PV_1_5;
}


inline const G4VPhysicalVolume* IronFilterDetectorConstruction::GetshieldcapironPV1_5() const {
  return shield_cap_iron_PV_1_5;
}


inline const G4VPhysicalVolume* IronFilterDetectorConstruction::GetDTsolidPV1_5() const {
  return DT_solid_PV_1_5;
}



inline const G4VPhysicalVolume* IronFilterDetectorConstruction::GetIronsolidPV1_5() const {
  return Iron_solid_PV_1_5;
}


//6th Detector type B

inline const G4VPhysicalVolume* IronFilterDetectorConstruction::GetshieldingleadPV1_6() const {
  return shielding_lead_PV_1_6;
}

//inline const G4VPhysicalVolume* IronFilterDetectorConstruction::GetmoderatorironPV1_6() const {
// return moderator_iron_PV_1_6;
//}

inline const G4VPhysicalVolume* IronFilterDetectorConstruction::GetfilteraluminumPV1_6() const {
  return filter_aluminum_PV_1_6;
}


inline const G4VPhysicalVolume* IronFilterDetectorConstruction::GetshieldcapironPV1_6() const {
  return shield_cap_iron_PV_1_6;
}


inline const G4VPhysicalVolume* IronFilterDetectorConstruction::GetDTsolidPV1_6() const {
  return DT_solid_PV_1_6;
}



inline const G4VPhysicalVolume* IronFilterDetectorConstruction::GetIronsolidPV1_6() const {
  return Iron_solid_PV_1_6;
}



//////////********* LAB ***********//////////////
inline const G4VPhysicalVolume* IronFilterDetectorConstruction::GetLabFloorWallsolidPV() const {
  return LabFloorWall_solid_PV;
}

inline const G4VPhysicalVolume* IronFilterDetectorConstruction::GetLabFloorExtendedsolidPV() const {
  return LabFloorExtended_solid_PV;
}

inline const G4VPhysicalVolume* IronFilterDetectorConstruction::GetfrontglassdoorPV() const {
  return frontglassdoor_PV;
}

inline const G4VPhysicalVolume* IronFilterDetectorConstruction::GetfrontdoorPV() const {
  return frontdoor_PV;
}

inline const G4VPhysicalVolume* IronFilterDetectorConstruction::GetglasswindowPV() const {
  return glasswindow_PV;
}

inline const G4VPhysicalVolume* IronFilterDetectorConstruction::GetreardoorPV() const {
  return reardoor_PV;
}

inline const G4VPhysicalVolume* IronFilterDetectorConstruction::GetInsulationPV() const {
  return Insulation_PV;
}


////////******Fridge*********////////////////
inline const G4VPhysicalVolume* IronFilterDetectorConstruction::GetDilutionUnitPV() const {
  return DilutionUnit_PV;
}

inline const G4VPhysicalVolume* IronFilterDetectorConstruction::GetMixingPlatePV() const {
  return MixingPlate_PV;
}

inline const G4VPhysicalVolume* IronFilterDetectorConstruction::GetColdPlate2PV() const {
  return ColdPlate2_PV;
}

inline const G4VPhysicalVolume* IronFilterDetectorConstruction::GetColdPlate1PV() const {
  return ColdPlate1_PV;
}

inline const G4VPhysicalVolume* IronFilterDetectorConstruction::GetOneKPlatePV() const {
  return OneKPlate_PV;
}

inline const G4VPhysicalVolume* IronFilterDetectorConstruction::GetOneKShieldPV() const {
  return OneKShield_PV;
}

inline const G4VPhysicalVolume* IronFilterDetectorConstruction::GetDilutionChamberPV() const {
  return DilutionChamber_PV;
}


inline const G4VPhysicalVolume* IronFilterDetectorConstruction::GetFourKPlatePV() const {
  return FourKPlate_PV;
}

inline const G4VPhysicalVolume* IronFilterDetectorConstruction::GetFourKShieldPV() const {
  return FourKShield_PV;
}

inline const G4VPhysicalVolume* IronFilterDetectorConstruction::GetSeventyKPlatePV() const {
  return SeventyKPlate_PV;
}


inline const G4VPhysicalVolume* IronFilterDetectorConstruction::GetSeventyKShieldPV() const {
  return SeventyKShield_PV;
}

inline const G4VPhysicalVolume* IronFilterDetectorConstruction::GetOVCShieldPV() const {
  return OVCShield_PV;
}


inline const G4VPhysicalVolume* IronFilterDetectorConstruction::GetBucketShieldingLeadPV() const {
  return BucketShielding_Lead_PV;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
