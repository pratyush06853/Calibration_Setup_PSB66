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
// $Id: IronFilterDetectorConstruction.cc $
//
/// \file IronFilterDetectorConstruction.cc
/// \brief Implementation of the IronFilterDetectorConstruction class

#include "IronFilterDetectorConstruction.hh"
#include "IronFilterDetectorMessenger.hh"//pratyush
#include "G4Material.hh"
#include "G4Isotope.hh"
#include "G4Element.hh"
#include "G4NeutronHPThermalScatteringNames.hh"
#include "G4UnitsTable.hh"
#include "G4NistManager.hh"

#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4Cons.hh"
#include "G4Sphere.hh"
#include "G4LogicalVolume.hh"
#include "G4RotationMatrix.hh"
#include "G4PVPlacement.hh"
#include "G4PVReplica.hh"
#include "G4AutoDelete.hh"
#include "G4UnionSolid.hh"
#include "G4SubtractionSolid.hh"
#include "G4Polycone.hh"

#include "G4GeometryManager.hh"
#include "G4PhysicalVolumeStore.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4SolidStore.hh"

#include "G4VisAttributes.hh"
#include "G4Colour.hh"

#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4ThreadLocal

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

IronFilterDetectorConstruction::IronFilterDetectorConstruction()
 : G4VUserDetectorConstruction(),
   LabFloorWall_solid_PV(0),
   LabFloorExtended_solid_PV(0),
   frontglassdoor_PV(0),
   frontdoor_PV(0),
   glasswindow_PV(0),
   reardoor_PV(0),
   Insulation_PV(0),
   DilutionUnit_PV(0),
   BucketShielding_Lead_PV(0),
   ////airlayer_solid_PV(0),
   ////room_solid_PV(0),
   //1st detector of type A
   shielding_lead_PV_2(0),
   filter_aluminum_PV_2(0),
   //moderator_iron_PV_2(0),
   shield_cap_iron_PV_2(0),
   /////inner_shield_PV(0),
   DT_solid_PV_2(0),
   Iron_solid_PV_2(0),
   //2nd detector of type A
   shielding_lead_PV(0),
   filter_aluminum_PV(0),
   //moderator_iron_PV(0),
   shield_cap_iron_PV(0),
   ////inner_shield_PV(0),
   DT_solid_PV(0),
   Iron_solid_PV(0),
   //3rd detector of type A
   shielding_lead_PV_3(0),
   filter_aluminum_PV_3(0),
   //moderator_iron_PV_3(0),
   shield_cap_iron_PV_3(0),
   /////inner_shield_PV(0),
   DT_solid_PV_3(0),
   Iron_solid_PV_3(0),
   //4th detector of type B
   shielding_lead_PV_1(0),
   filter_aluminum_PV_1(0),
   //moderator_iron_PV_1(0),
   shield_cap_iron_PV_1(0),
   /////inner_shield_PV_1(0),
   DT_solid_PV_1(0),
   Iron_solid_PV_1(0),
   //5th detector of type B
   shielding_lead_PV_1_5(0),
   filter_aluminum_PV_1_5(0),
   //moderator_iron_PV_1_5(0),
   shield_cap_iron_PV_1_5(0),
   /////inner_shield_PV_1_5(0),
   DT_solid_PV_1_5(0),
   Iron_solid_PV_1_5(0),
   //6th detector of type B
   shielding_lead_PV_1_6(0),
   filter_aluminum_PV_1_6(0),
   //moderator_iron_PV_1_6(0),
   shield_cap_iron_PV_1_6(0),
   /////inner_shield_PV_1_6(0),
   DT_solid_PV_1_6(0),
   Iron_solid_PV_1_6(0),
   fCheckOverlaps(true)
{
  //for messenger, you vary these variables using the macro
  fMultiplierLeadHeightRear = 20.0*cm;//20.0*cm
  fMultiplierLeadHeightFront=  15.0*cm;//30.0*cm

  fModeratorAluminumHeight= 30.0*cm;//39.0*cm
  fModeratorTitaniumHeight= (5.0)*cm; //(34.0)*cm

  fMultiplierLeadRadius = 20.0*cm;//20.0*cm
  fModeratorAluminumRadius = 15.0*cm;//15.0*cm without Ti
  fModeratorTitaniumRadius = 15.0*cm;

  //fPolyHeight = 41.0*cm;//
  //fPolyHeight = 35.0*cm;//
  fPolyHeight = 30.0*cm;//this shouldn't change

  //fFilterCellSpacing= 50.0*cm;//5
  fFilterCellSpacing= 50.0*cm+26.0*cm;//5

  ftestx = 0*m;
  ftesty = 0*m;
  ftestz = 0.0*m;



  fDetectorMessenger = new IronFilterDetectorMessenger(this);
  //
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

IronFilterDetectorConstruction::~IronFilterDetectorConstruction()
{
  delete fDetectorMessenger;//Pratyush
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* IronFilterDetectorConstruction::Construct()
{
  // Define materials
  DefineMaterials();
  // Define volumes
  return DefineVolumes();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void IronFilterDetectorConstruction::DefineMaterials()
{
  G4double a;  // mass of a mole;
  G4double z;  // z=mean number of protons;
  G4double density, fractionMass;
  G4String symbol, name;
  G4int nComponents, nAtoms;
  G4double temp;
  G4NistManager* NistMgr = G4NistManager::Instance();

  G4Element* elH  = new G4Element(name = "Hydrogen", symbol = "H", z = 1.0, a = 1.008*g/mole);
  G4Element* elLi6 = new G4Element(name = "Lithium6", symbol = "Li", z = 3.0, a = 6.015122*g/mole);
  G4Element* elLi7 = new G4Element(name = "Lithium6", symbol = "Li", z = 3.0, a = 7.016003*g/mole);
  G4Element* elB10 = new G4Element(name = "Boron10", symbol = "B", z = 5.0, a = 10.00*g/mole);
  G4Element* elB11 = new G4Element(name = "Boron11", symbol = "B", z = 5.0, a = 11.00*g/mole);
  G4Element* elB  = new G4Element(name = "Boron", symbol = "B", z = 5.0, a = 10.811*g/mole);
  G4Element* elC  = new G4Element(name = "Carbon", symbol = "C", z = 6.0, a = 12.011*g/mole);
  G4Element* elN = new G4Element("Nitrogen", symbol = "N",z = 7.,a = 14.01*g/mole);
  G4Element* elO  = new G4Element(name = "Oxygen", symbol = "O", z = 8.0, a = 15.999*g/mole);
  G4Element* elF = new G4Element(name= "Fluorine", symbol = "F", z = 9.0, a= 18.998403*g/mole); //pratyush
  G4Element* elNa = new G4Element("Sodium",symbol ="Na",z = 11.,a= 22.99*g/mole);
  G4Element* elMg = new G4Element("Magnesium",symbol ="Mg",z = 12.,a= 24.305*g/mole);
  G4Element* elAl  = new G4Element(name = "Aluminum", symbol = "Al", z = 13.0, a = 26.982*g/mole);
  G4Element* elSi  = new G4Element("Silicon", symbol = "Si", z = 14.0, a = 28.085*g/mole);
  G4Element* elP = new G4Element("Phosphorus",symbol ="P",z = 15.,a= 30.974*g/mole);
  G4Element* elS  = new G4Element(name = "sulphur", symbol = "S", z = 16.0, a = 32.065*g/mole);
  G4Element* elCl = new G4Element("Chlorine",symbol ="Cl",z = 17.,a= 35.453*g/mole);
  G4Element* elK = new G4Element("Potassium",symbol ="K",z = 19.,a= 39.098*g/mole);
  G4Element* elCa = new G4Element("Calcium",symbol ="Ca",z = 20.,a= 40.08*g/mole);
  G4Element* elFe  = new G4Element("Iron",symbol ="Fe",z = 26.,a= 55.85*g/mole);
  G4Element* elZn  = new G4Element(name = "zinc", symbol = "Ti", z = 30.0, a = 65.38*g/mole);
  G4Element* elRb = new G4Element("Rb",symbol ="Rb",z = 37.,a= 85.47 *g/mole);
  G4Element* elSr = new G4Element("Sr",symbol ="Sr",z = 38.,a= 87.62 *g/mole);
  G4Element* elZr = new G4Element("Zr",symbol ="Zr",z = 40.,a= 91.22 *g/mole);
  G4Element* elI  = new G4Element(name = "Iodine", symbol = "I", z = 53.0, a = 126.904473*g/mole);
  G4Element* elPb = new G4Element("Lead",symbol ="Pb", z = 82.,a= 207.19 *g/mole);

  G4Element *TS_H_P = new G4Element("TS_H_of_Polyethylene", "H", 1, 1.007*g/mole);
  G4Element *TS_H_W = new G4Element("TS_H_of_Water", "H", 1, 1.007*g/mole);


  //G4Element* elBe = new G4Element(name = "Beryllium", symbol = "Be", z = 4.0, a = 9.012*g/mole);
  //G4Element* elLi  = new G4Element(name = "Lithium", symbol = "Li", z = 3.0, a = 6.015*g/mole);
  //G4Element* elCr  = new G4Element(name = "Chromium", symbol = "Cr", z = 24.0, a = 51.996*g/mole);
  //G4Element* elFe  = new G4Element(name = "Iron", symbol = "Fe", z = 26.0, a = 55.845*g/mole);
  //G4Element* elNi  = new G4Element(name = "Nickel", symbol = "Ni", z = 28.0, a = 58.693*g/mole);
  //G4Element* elMo  = new G4Element(name = "Molybdenum", symbol = "Mo", z = 42.0, a = 95.94*g/mole);
  //G4Element* elI  = new G4Element(name = "Iodine", symbol = "I", z = 53.0, a = 127*g/mole);


  //Vacuum
  new G4Material("galactic", z = 1.0, a = 1.01*g/mole, density = universe_mean_density, kStateGas, 2.73*kelvin, 3.e-18*pascal);


  //helium
  new G4Material("liquid_helium", z = 2., a = 4.00*g/mole, density = 0.145*g/cm3, kStateLiquid, temp = 3.*kelvin);

  // Lead
  new G4Material(name = "Pb", z = 82.0, a = 207.2*g/mole, density = 11.34*g/cm3);
  new G4Material("NatLead", 82.0, 207.19*g/mole,  11.36*g/cm3, kStateSolid, 296*kelvin);

  //Copper
  new G4Material("NatCu", z =29.,  a =63.55*g/mole,density =   8.96 *g/cm3);

  // Iron
  new G4Material("NatIron", z = 26.0, a = 55.845*g/mole, density = 7.874*g/cm3);

  // scandium
  new G4Material("NatScandium", z = 21.0, a = 44.95*g/mole, density = 2.985*g/cm3);

  //Aluminum
  new G4Material("NatAluminum", z = 13.0, a = 26.9815384*g/mole, density = 2.70*g/cm3, kStateSolid, 296*kelvin);


  //Natural B
  G4Element* NatB=NistMgr->FindOrBuildElement("B");
  //Natural C
  G4Element* NatC=NistMgr->FindOrBuildElement("C");
  //Natural H
  G4Element* NatH=NistMgr->FindOrBuildElement("H");
  //Natural Oxygen
  G4Element* NatO=NistMgr->FindOrBuildElement("O");
  //Natural Na
  G4Element* NatNa=NistMgr->FindOrBuildElement("Na");


  // Silicon
  G4Isotope* Si28 = new G4Isotope("Si28", 14, 28, 27.9769265350*g/mole);
  G4Isotope* Si29 = new G4Isotope("Si29", 14, 29, 28.9764946653*g/mole);
  G4Isotope* Si30 = new G4Isotope("Si30", 14, 30, 29.973770137*g/mole);

  G4Element* NatSi = new G4Element("silicon_natural", "Si",3);
  NatSi->AddIsotope(Si28,92.2*perCent);
  NatSi->AddIsotope(Si29,4.7*perCent);
  NatSi->AddIsotope(Si30,3.1*perCent);

  G4Material* silicon = new G4Material("silicon", 2.3290*g/cm3,1, kStateSolid, 296*kelvin);
  silicon->AddElement(NatSi, 1);



  // Carbon
  G4Isotope* C12 = new G4Isotope("C12", 6, 12, 12*g/mole);
  G4Isotope* C13 = new G4Isotope("C13", 6, 13, 13.003355*g/mole);

  G4Element* carbon = new G4Element("carbon_natural", "C",2);
  carbon->AddIsotope(C12,98.9*perCent);
  carbon->AddIsotope(C13,1.1*perCent);

  G4Material* diamond = new G4Material("diamond", 3.51*g/cm3, 1, kStateSolid, 296*kelvin);
  diamond->AddElement(carbon, 1);


  // Titanium
  G4Isotope* Ti46 = new G4Isotope("Ti46", 22, 46, 45.9526316*g/mole);
  G4Isotope* Ti47 = new G4Isotope("Ti47", 22, 47, 46.9517631*g/mole);
  G4Isotope* Ti48 = new G4Isotope("Ti48", 22, 48, 47.9479463*g/mole);
  G4Isotope* Ti49 = new G4Isotope("Ti49", 22, 49, 48.9478700*g/mole);
  G4Isotope* Ti50 = new G4Isotope("Ti50", 22, 50, 49.9447912*g/mole);

  G4Element* NatTi = new G4Element("titanium_natural", "Ti",5);
  NatTi->AddIsotope(Ti46,8.25*perCent);
  NatTi->AddIsotope(Ti47,7.44*perCent);
  NatTi->AddIsotope(Ti48,73.72*perCent);
  NatTi->AddIsotope(Ti49,5.41*perCent);
  NatTi->AddIsotope(Ti50,5.18*perCent);

  G4Material* titanium = new G4Material("titanium", 4.507*g/cm3,1, kStateSolid, 296*kelvin);
  titanium->AddElement(NatTi, 1);

  //Germanium
  G4Isotope* Ge70 = new G4Isotope("Ge70", 32, 70, 69.924249*g/mole);
  G4Isotope* Ge72 = new G4Isotope("Ge72", 32, 72, 46.9517631*g/mole);
  G4Isotope* Ge73 = new G4Isotope("Ge73", 32, 73, 47.9479463*g/mole);
  G4Isotope* Ge74 = new G4Isotope("Ge74", 32, 74, 48.9478700*g/mole);
  G4Isotope* Ge75 = new G4Isotope("Ge75", 32, 75, 49.9447912*g/mole);

  G4Element* NatGe = new G4Element("germanium_natural", "Ti",5);
  NatGe->AddIsotope(Ge70,20.52*perCent);
  NatGe->AddIsotope(Ge72,27.45*perCent);
  NatGe->AddIsotope(Ge73,7.76*perCent);
  NatGe->AddIsotope(Ge74,36.7*perCent);
  NatGe->AddIsotope(Ge75,7.57*perCent);

  G4Material* germanium = new G4Material("germanium", 5.323*g/cm3,1, kStateSolid, 296*kelvin);
  germanium->AddElement(NatGe, 1);


  //Ni60
  G4Material* Ni60 = new G4Material("Ni60", z = 28.0, a = 59.9307864*g/mole, density = 8.9*g/cm3);
  //Fe54
  G4Material* Fe54 = new G4Material("Fe54", z = 26.0, a = 	53.9396090*g/mole, density = 7.874*g/cm3);
  //Co
  G4Material* NatCo = new G4Material("NatCo", z = 27.0, a = 	58.933*g/mole, density = 8.86*g/cm3);





  //LiI
  G4Isotope* Li6 = new G4Isotope("Li6", 3, 6, 6.01*g/mole);
  G4Isotope* Li7 = new G4Isotope("Li7", 3, 7, 7.01*g/mole);

  G4Element* Li6enriched = new G4Element("Lithium_enchried", "Li",2);
  Li6enriched->AddIsotope(Li6,97.0*perCent);
  Li6enriched->AddIsotope(Li7,3.0*perCent);

  G4Material* Li6F = new G4Material("Li6F", density= 2.64 * g / cm3,nComponents= 2, kStateSolid, 296*kelvin);
  Li6F->AddElement(Li6enriched, 1);
  Li6F->AddElement(elF,1);

  G4Material* ZnS = new G4Material("ZnS", density= 4.09 * g / cm3,nComponents= 2, kStateSolid, 296*kelvin);
  ZnS->AddElement(elZn, 1);
  ZnS->AddElement(elS,1);

  //Remeber HD has 1:2 LiF to ZnS concentration
  G4Material* ej_426_HD= new G4Material( "ej_426_HD", density=3.60*g/cm3, nComponents=2, kStateSolid, 296*kelvin);
  ej_426_HD->AddMaterial( Li6F, 33.3*perCent );   //1.026*g/cm3
  ej_426_HD->AddMaterial( ZnS, 66.7*perCent );


  //Polyethylene moderator
  G4Material*  polyethylene = new G4Material("polyethylene", density=0.94*g/cm3, nComponents=2,kStateSolid, 296*kelvin);
  polyethylene->AddElement(NatC, 1);
  polyethylene->AddElement(TS_H_P, 2);

  // Assuming PMMA -- see
  //	http://en.wikipedia.org/wiki/Poly(methyl_methacrylate)
  G4Material*  acrylic = new G4Material("acrylic", density= 1.17 * g/cm3, nComponents=3 ,kStateSolid, 296*kelvin);
  acrylic->AddElement(NatC, 5);
  acrylic->AddElement(elO, 2);
  acrylic->AddElement(TS_H_P, 8);

  //Water
  G4Material* water = new G4Material("water", density= 1.00 * g / cm3,nComponents= 2, kStateLiquid, 296*kelvin);
  water->AddElement(TS_H_W,2);
  water->AddElement(elO,1);

  //Aluminum Fluoride
  G4Material* AlF3 = new G4Material("AlF3", density= 3.10 * g / cm3,nComponents= 2); //pratyush
  AlF3->AddElement(elAl, 1);  //pratyush
  AlF3->AddElement(elF, 3);   //pratyush

  //Borax
  G4Material* Borax = new G4Material("Borax", density= 0.76* g / cm3,nComponents= 4,kStateSolid, 296*kelvin); //pratyush
  Borax->AddElement(NatNa,12.06*perCent);//2
  Borax->AddElement(NatB,11.34*perCent);//4
  Borax->AddElement(NatH,5.29*perCent);//20
  Borax->AddElement(NatO,71.32*perCent);//17

  //Boric Acid https://www.convertunits.com/molarmass/Boric+Acid
  G4Material* boric_acid = new G4Material("boric_acid", density= 1.44* g / cm3,nComponents= 3,kStateSolid, 296*kelvin); //pratyush
  boric_acid->AddElement(NatH,4.890*perCent);//3
  boric_acid->AddElement(NatB,17.484*perCent);//1
  boric_acid->AddElement(NatO,77.626*perCent);//3

  //Borax_water_Mixture(5.8% solubity of borax https://omsi.edu/sites/all/FTP/files/kids/Borax-msds.pdf)
  //mixture of 5.5% Borax and 94.5% of Water
  G4Material* borax_water = new G4Material( "borax_water",density= 0.9868*g/cm3, nComponents= 2,kStateLiquid, 296*kelvin); //pratyush
  borax_water->AddMaterial( Borax, 5.5*perCent );
  borax_water->AddMaterial( water, 94.5*perCent );


  //Borax_BoricAcid_buffer(https://www.researchgate.net/publication/244069630_Preparation_of_highly_concentrated_aqueous_solution_of_sodium_borate)
  //mixture of 20g BoricAcid, 25g of Borax and 100g of water
  G4Material* borax_boricacid_buffer = new G4Material( "borax_boricacid_buffer",density= 1.019*g/cm3, nComponents= 3,kStateLiquid, 296*kelvin);
  borax_boricacid_buffer->AddMaterial( boric_acid, 13.7*perCent );//pratyush
  borax_boricacid_buffer->AddMaterial( Borax, 17.2*perCent );//pratyush
  borax_boricacid_buffer->AddMaterial( water, 69.1*perCent );//pratyush

  //Fluental
  //mixture of 40% Al and 60% of AlF_3
  G4Material* fluental = new G4Material( "fluental",density= 2.94*g/cm3, nComponents= 2); //pratyush
  fluental->AddMaterial( AlF3, 60.*perCent );
  fluental->AddElement( elAl, fractionMass = 40.*perCent );

  //polyethyleneBorated 3 % borated poly
  G4Material* boratedPoly = new G4Material( "boratedPoly", density=1.19*g/cm3, nComponents=3,kStateSolid, 296*kelvin);
  boratedPoly->AddElement( NatB, 3.*perCent );
  boratedPoly->AddElement( NatC, 82.576*perCent );
  boratedPoly->AddElement(TS_H_P, 14.424*perCent );

  //from vivian communicated via whatsapp
  //https://docs.google.com/spreadsheets/d/1W83GhE5Nq1R9f7KmCgBqi_Qkz0ilursgWs5V-Vmju8o/edit#gid=656123429
  G4Material* boratedPoly_15 = new G4Material("boratedPoly_15", density=1.15*g/cm3, nComponents=3,kStateSolid, 296*kelvin);
  boratedPoly_15->AddElement(NatB, 15*perCent);
  boratedPoly_15->AddElement(NatC, 73.38*perCent);
  boratedPoly_15->AddElement(TS_H_P, 11.62*perCent);


  //wood
  G4Material* wood = new G4Material("wood", density=0.9*g/cm3, nComponents=3);
  wood->AddElement(TS_H_P , 4);
  wood->AddElement(elO , 1);
  wood->AddElement(elC, 2);

  G4Material* quartz = new G4Material("quartz", density=2.200*g/cm3, nComponents=2);
  quartz->AddElement(elSi, 1);
  quartz->AddElement(elO , 2);

  G4Material*soft_tissue = new G4Material("soft_tissue",density= 0.9869*g/cm3,nComponents=9);
  soft_tissue->AddElement(elH,0.105);
  soft_tissue->AddElement(elC,0.256);
  soft_tissue->AddElement(elN,0.027);
  soft_tissue->AddElement(elO,0.602);
  soft_tissue->AddElement(elNa,0.001);
  soft_tissue->AddElement(elP,0.002);
  soft_tissue->AddElement(elS,0.003);
  soft_tissue->AddElement(elCl,0.002);
  soft_tissue->AddElement(elK,0.002);


  //soil
  G4Material*soil = new G4Material("soil",density= 1.50*g/cm3,nComponents=8);
  soil->AddElement(elH,0.021);
  soil->AddElement(elC,0.016);
  soil->AddElement(elO,0.577);
  soil->AddElement(elAl,0.050);
  soil->AddElement(elSi,0.271);
  soil->AddElement(elK,0.013);
  soil->AddElement(elCa,0.041);
  soil->AddElement(elFe,0.011);

  //concrete
  G4Material*concrete = new G4Material("concrete",density= 2.3*g/cm3,nComponents=10);
  concrete->AddElement(elH,0.01);
  concrete->AddElement(elC,0.001);
  concrete->AddElement(elO,0.529107);
  concrete->AddElement(elNa,0.016);
  concrete->AddElement(elMg,0.002);
  concrete->AddElement(elAl,0.033872);
  concrete->AddElement(elSi,0.337021);
  concrete->AddElement(elK,0.013);
  concrete->AddElement(elCa,0.044);
  concrete->AddElement(elFe,0.014);

  //concrete
  //G4Material*concrete = new G4Material("concrete",density= 2.3*g/cm3,nComponents=10);
  G4Material*HDconcrete = new G4Material("HDconcrete",density= 4.81*g/cm3,nComponents=10);
  HDconcrete->AddElement(elH,0.01);
  HDconcrete->AddElement(elC,0.001);
  HDconcrete->AddElement(elO,0.529107);
  HDconcrete->AddElement(elNa,0.016);
  HDconcrete->AddElement(elMg,0.002);
  HDconcrete->AddElement(elAl,0.033872);
  HDconcrete->AddElement(elSi,0.337021);
  HDconcrete->AddElement(elK,0.013);
  HDconcrete->AddElement(elCa,0.044);
  HDconcrete->AddElement(elFe,0.014);


  //borated concrete
  G4Material* borated_concrete = new G4Material("borated_concrete",density= 2.32*g/cm3,nComponents=10);
  borated_concrete->AddElement(elH,0.96*perCent);
  borated_concrete->AddElement(elC,5.36*perCent);
  borated_concrete->AddElement(elO,51.3*perCent);
  borated_concrete->AddElement(NatB,2.9*perCent);
  borated_concrete->AddElement(elMg,0.42*perCent);
  borated_concrete->AddElement(elAl,0.79*perCent);
  borated_concrete->AddElement(elSi,15.7*perCent);
  borated_concrete->AddElement(elS,0.42*perCent);
  borated_concrete->AddElement(elCa,23*perCent);
  borated_concrete->AddElement(elFe,0.50*perCent);



  // Print materials
  //G4cout <<"Is hydrogen declared in the scintillator a Thermal Hydrogen"  <<G4NeutronHPThermalScatteringNames::IsThisThermalElement(TS_H_of_Polyethylene)<< G4endl;
  G4cout << *(G4Material::GetMaterialTable()) << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* IronFilterDetectorConstruction::DefineVolumes()
{

  // Get materials
  G4Material* Vacuum = G4Material::GetMaterial("galactic");
  G4Material* Helium = G4Material::GetMaterial("liquid_helium");
  G4Material* Titanium = G4Material::GetMaterial("titanium");
  G4Material* Aluminum = G4Material::GetMaterial("NatAluminum");
  G4Material* Lead = G4Material::GetMaterial("NatLead");
  G4Material* Silicon = G4Material::GetMaterial("silicon");
  G4Material* Diamond = G4Material::GetMaterial("diamond");
  G4Material* Germanium = G4Material::GetMaterial("germanium");
  G4Material* Iron = G4Material::GetMaterial("NatIron");
  G4Material* Scandium = G4Material::GetMaterial("NatScandium");
  G4Material* Fluental = G4Material::GetMaterial("fluental");
  G4Material* BoraxWater = G4Material::GetMaterial("borax_water");
  G4Material* BoraxBoricAcidBuffer = G4Material::GetMaterial("borax_boricacid_buffer");
  G4Material* Copper= G4Material::GetMaterial("NatCu");

  G4Material* EJ4265HD = G4Material::GetMaterial("ej_426_HD");
  G4Material* Polyethylene = G4Material::GetMaterial("polyethylene");
  G4Material* Acrylic = G4Material::GetMaterial("acrylic");
  G4Material* BoratedPoly_15 = G4Material::GetMaterial("boratedPoly_15");
  G4Material*  Soft_Tissue=G4Material::GetMaterial("soft_tissue");
  G4Material*  Concrete = G4Material::GetMaterial("concrete");
  G4Material*  Borated_Concrete = G4Material::GetMaterial("borated_concrete");
  G4Material*  Wood = G4Material::GetMaterial("wood");
  G4Material*  Quartz = G4Material::GetMaterial("quartz");
    G4Material* Water = G4Material::GetMaterial("water");
  G4Material*  Soil = G4Material::GetMaterial("soil");


  if ( ! Vacuum ) {
    G4ExceptionDescription msg;
    msg << "Cannot retrieve materials already defined.";
    G4Exception("IronFilterDetectorConstruction::DefineVolumes()",
      "MyCode0001", FatalException, msg);
  }



//
// Sizes
//




  G4double DD_Height = 20.0*cm;
  G4double DD_Extra_Height= 60.0*cm;
  G4double shieldthickness = 40.0*cm; //20.0*cm; //20
  G4double leadshieldthickness = 20.0*cm;
  G4double Polyshieldthickness = 40.0*cm;
  G4double SourceRadius = 1.7*cm;
  G4double delta= 1.0*cm;// 1.0cm parameter of catchment area



  ///////////***********lab room************//////////////////
  //G4double colimator_length=26.0*cm;
  //G4double colimator_length=30.0*cm;
  G4double colimator_length=33.0*cm;
  G4double fFilterCellSpacing= 50.0*cm+36.0*cm;//50.0*cm+26.0*cm;

  G4double Side_shield_thickness=20.0*cm;


  //
  //  calculate the Sizes of some derived units.
  //
  G4double Scandium_diameter_limited=3.5*cm;//3.5*cm;5*cm;
  G4double Scandium_height_limited=30*cm;//30*cm;
  //G4double Pb_radius = fSource_radius + 5.0*cm ;


  G4double NeutronFilter_length = fMultiplierLeadHeightRear+fMultiplierLeadHeightFront+fModeratorAluminumHeight+fModeratorTitaniumHeight+fPolyHeight;


  //G4double Water_rear_side = 20.0*cm ;
  G4double Water_rear_side = 55.0*cm ;
  //G4double Water_x = 200.0*cm;
  G4double Water_x = 240.0*cm;
  G4double Water_y = NeutronFilter_length+Water_rear_side;
  //G4double Water_z = 200.0*cm;
  G4double Water_z = 232.0*cm;

  G4double DT_Ti_T_location = 207.5*mm;
  G4double Insulation_Thickness = 5*mm;


  G4double Water_cylindercal_can_radius = 152.7175*cm;
  //G4double Water_cylindercal_can_radius_x = 120*cm;
  G4double Water_cylindercal_can_radius_x = 30*cm+152.7175*cm;//152.7175*cm;
  //G4double Water_cylindercal_can_radius_x = 152.7175*cm;
  G4double Water_cylindercal_can_height = 115.8875*cm;
  G4double ConcreteSupport_height = 99.0*cm; //80cm  110.0*cm


  G4double Poly_a = 40.0*cm;
  G4double hole_length = NeutronFilter_length-(fMultiplierLeadHeightRear+fMultiplierLeadHeightFront)-fModeratorAluminumHeight-fModeratorTitaniumHeight;
  //G4double hole_length = NeutronFilter_length-(fMultiplierLeadHeightRear+fMultiplierLeadHeightFront)-fModeratorAluminumHeight-fModeratorTitaniumHeight;
  //G4double colimator_length=26.0*cm;
  //G4double colimator_length=30.0*cm;

  //G4double Side_shield_thickness=20.0*cm;

  G4double Titanium_shield_height= 5*cm ;
  G4double Manganese_shield_height= 10*cm;

  G4double lab68_wall_thickness = 25.0*cm ;
  //distance from the outer egdes
  G4double lab68_wall_x = 6.654*m ;
  G4double lab68_wall_y = 9.35063*m ;
  G4double lab68_wall_z = 5.636*m ;

  G4double Pump_chase_y = 2.9*m ;

  G4double lab68_frontdoor_glass_height = 2.9*m;
  G4double lab68_frontdoor_glass_width = 2.2*m;

  G4double lab68_frontdoor_wood_height = 2.3*m;
  G4double lab68_frontdoor_wood_width = 1.5*m;

  G4double lab68_glasswindow_height = 1.08*m;
  G4double lab68_glasswindow_width = 0.57*m;

  G4double lab68_reardoor_height = 2.3*m;
  G4double lab68_reardoor_width = 0.91*m;

  G4double lab68_frontdoor_x_coordinate = lab68_wall_x/2 -lab68_frontdoor_glass_width/2.0-1.2*m;
  G4double lab68_reardoor_x_coordinate = -lab68_wall_x/2.0 +lab68_reardoor_width/2.0+2.613*m;

G4ThreeVector position_of_origin = {3.221*m, -2.603*m, 1.4547*m};


  G4ThreeVector xyposition_of_origin = {2.721*m, -2.703*m, 0};

  G4double Phantom_Radius=0.4*m;
  G4double Phantom_Height=2.0*m;
  //G4double Phantom_Size=0.25*m;
  G4double Phantom_Size=0.25*m/2.0;
  G4double Li6F_thickness=1.0*cm;



  //Fridge
  G4double SeventyKShield_Width = 0.2*cm;
  G4double SeventyKShield_Radius = 18.95*cm;
  G4double SeventyKShield_Height = 1.28*m;

  G4double OVCShield_Width = 0.4*cm;
  G4double OVCShield_Radius = 21.1*cm;
  G4double OVCShield_Height = 1.5*m;

  G4double FourKShield_Width = 0.2*cm;
  G4double FourKShield_Radius = 17.2*cm;
  G4double FourKShield_Height = 1.048*m;

  G4double OneKShield_Width = 0.2*cm;
  G4double OneKShield_Radius = 15.65*cm;
  G4double OneKShield_Height = 0.881*m;

  //G4double DilutionUnit_Radius = 10.0*cm;
  //G4double DilutionUnit_Radius = 2.0*cm;//5.0*cm;
  //G4double DilutionUnit_Height = 3.0*cm;

  //G4double DilutionChamber_Radius = DilutionUnit_Radius;//10.0*cm
  //G4double DilutionChamber_Height = DilutionUnit_Height + 5.3*cm;//15.3*cm
  //G4double DilutionChamber_Width = 2.0*mm;
  //G4double DilutionChamber_bottomplate_thick = 5*mm;
  //G4double DilutionChamber_upperplate_thick = 3*mm;


//G4double DilutionUnit_Radius = 10.0*cm;
G4double DilutionUnit_Radius = 3.0*cm;//5.0*cm;
G4double DilutionUnit_Height = 5.0*cm;

G4double DilutionChamber_Radius =5.0*cm ;//4.0*cm
G4double DilutionChamber_UpperPart_Radius =15.24/2.0*cm ;
G4double DilutionChamber_Height = 11.5*cm;
G4double DilutionChamber_Width = 2.0*mm;
G4double DilutionChamber_bottomplate_thick = 0.5*cm;
G4double DilutionChamber_upperplate_thick = (0.95+1.43+1.11)*cm;


  G4double SeventyKPlate_Radius = 20.0*cm;
  G4double FourKPlate_Radius = 18.3*cm;
  G4double OneKPlate_Radius = 16.7*cm;
  G4double ColdPlate1_Radius = 15.0*cm;
  G4double ColdPlate2_Radius = 15.0*cm;
  G4double MixingPlate_Radius = 15.0*cm;

  G4double SeventyKPlate_Thickness = 0.4*cm;
  G4double FourKPlate_Thickness  = 0.4*cm;
  G4double OneKPlate_Thickness  = 0.4*cm;
  G4double ColdPlate1_Thickness  = 0.4*cm;
  G4double ColdPlate2_Thickness  = 0.4*cm;
  G4double MixingPlate_Thickness  = 0.5*cm;

  G4double OVC_z = 10.3*cm;
  G4double SeventyKPlate_z = 20.3*cm+ FourKPlate_Thickness/2.0 + SeventyKPlate_Thickness/2.0;
  G4double FourKPlate_z  = 14.1*cm+ OneKPlate_Thickness/2.0 + FourKPlate_Thickness/2.0;
  G4double OneKPlate_z  = 9.4*cm + ColdPlate1_Thickness/2.0 + OneKPlate_Thickness/2.0;
  G4double ColdPlate1_z  = 9.6*cm + ColdPlate1_Thickness/2.0+ ColdPlate2_Thickness/2.0;
  G4double ColdPlate2_z  = 16*cm + MixingPlate_Thickness/2.0+ ColdPlate2_Thickness/2.0;
  //G4double MixingPlate_z  = 10.4*cm + MixingPlate_Thickness/2;
  G4double MixingPlate_z  = 21.7*cm + MixingPlate_Thickness/2;


  ///backing Detector
  G4double zeroRadius = 0.*cm;
  G4double startAngle = 0.*deg;
  G4double spanningAngle = 360.*deg;
  //G4double shieldHeight = 400.*cm;

  //G4double moderatorRadius = 15.0*cm; //15
  //G4double Front_Moderator_Thickness=(1.0/2.0)*2.54*cm; //changes this
  //G4double Back_Moderator_Thickness=(1.0/2.0)*2.54*cm;
  G4double Front_Moderator_Thickness=1.5*cm; //changes this
  G4double Back_Moderator_Thickness=1.5*cm;
  //G4double Inner_Radius =30.0*cm;
  G4double Inner_Radius =30.0*cm;
  G4double Radial_thickness=10.0*cm;//10.0*cm;
  G4double Mid_Acrylic_thickness=2.5*cm;
  //G4double Mid_Acrylic_thickness=(4.0/4.0)*2.54*cm;
  G4double EJ426_thickness=0.25*2*mm;
  G4double BoratedPoly_thickness = 5.0*cm; //15
  //G4double shieldCapHeight= 15.0*cm;//5
  //G4double DilutionUnit_Radius = 10.0*cm;
  //G4double DilutionUnit_Height = 5.0*cm;


  G4double shieldHeight =  Front_Moderator_Thickness+Mid_Acrylic_thickness+Back_Moderator_Thickness;






//
// Rotations
//

  G4RotationMatrix* NO_ROT = new G4RotationMatrix;
  G4RotationMatrix* xRot7 = new G4RotationMatrix;
  G4RotationMatrix* xRot8 = new G4RotationMatrix;
  xRot7 -> rotateX(-pi/2.*rad);
  xRot8 -> rotateX(pi/2.*rad);

  G4RotationMatrix* turnAlongX = new G4RotationMatrix;
  turnAlongX->rotateX(90*deg);

  G4RotationMatrix* turnAlongXY = new G4RotationMatrix;
  turnAlongXY->rotateZ(90*deg);
  turnAlongXY->rotateZ(-100*deg);

  G4RotationMatrix* turnAlong = new G4RotationMatrix;
  turnAlong->rotateZ(10*deg);
  //turnAlong->rotateY(10*deg);

  G4RotationMatrix* turnAlong190 = new G4RotationMatrix;
  turnAlong190->rotateZ(190*deg);

  G4RotationMatrix* turnAlongZ = new G4RotationMatrix;
  turnAlongZ->rotateZ(90*deg);
  turnAlongZ->rotateZ(-90*deg);

//
// GEOMETRY
//

  G4double second_detector_z =  70.0*cm;


  //G4VSolid* vacuum_solid = new G4Tubs("vacuum_solid", zeroRadius,Inner_Radius+ Radial_thickness+20.0*cm, 100.0*cm, startAngle, spanningAngle);
  G4VSolid* vacuum_solid =new G4Box("vacuum_solid", 150.0*m, 150.0*m, 150.0*m);
  //G4VSolid* vacuum_solid = new G4Box("vacuum_solid", CapturerLength/2.0, CapturerLength/2.0, (shieldHeight)/2.0);
  G4LogicalVolume* vacuum_solid_LV = new G4LogicalVolume(vacuum_solid, Vacuum, "vacuum_solid");
  G4VPhysicalVolume* vacuum_solid_PV = new G4PVPlacement(NO_ROT, G4ThreeVector(), vacuum_solid_LV, "Vacuum_solid", 0, false, 0, fCheckOverlaps);


  //Lab66
  G4VSolid* Main_2_S = new G4Box("Main_2_solid", lab68_wall_x/2.0, lab68_wall_y/2.0 , lab68_wall_z/2.0);
  G4VSolid* hole_2_S = new G4Box("hole_2_solid", (lab68_wall_x-lab68_wall_thickness)/2.0, (lab68_wall_y-2*lab68_wall_thickness)/2.0, (lab68_wall_z-2*lab68_wall_thickness)/2.0);
  G4SubtractionSolid* LabFloorWall_solid_S= new G4SubtractionSolid("LabFloorWall_solid", Main_2_S, hole_2_S, NO_ROT, G4ThreeVector(0.,0., 0.));
  G4LogicalVolume* LabFloorWall_solid_LV = new G4LogicalVolume(LabFloorWall_solid_S, Concrete, "LabFloorWall_solid");
  LabFloorWall_solid_PV = new G4PVPlacement(turnAlong, G4ThreeVector{lab68_wall_x/2.0,-lab68_wall_y/2.0,lab68_wall_z/2.0}-position_of_origin, LabFloorWall_solid_LV, "LabFloorWall", vacuum_solid_LV, false, 0, fCheckOverlaps);
  LabFloorWall_solid_LV->SetVisAttributes(G4VisAttributes(G4Colour::Grey()));

  G4VSolid* frontglassdoor_S = new G4Box("frontglassdoor_solid", lab68_frontdoor_glass_width/2.0, lab68_wall_thickness/2.0, lab68_frontdoor_glass_height/2.0);
  G4LogicalVolume* frontglassdoor_LV = new G4LogicalVolume(frontglassdoor_S, Quartz, "frontglassdoor");
  frontglassdoor_PV = new G4PVPlacement(NO_ROT, G4ThreeVector(lab68_frontdoor_x_coordinate ,-(lab68_wall_y-lab68_wall_thickness)/2.0, -(lab68_wall_z-2*lab68_wall_thickness-lab68_frontdoor_glass_height)/2.0), frontglassdoor_LV, "Front Glass Door", LabFloorWall_solid_LV, false, 0, fCheckOverlaps);
  frontglassdoor_LV->SetVisAttributes(G4VisAttributes(G4Colour::Cyan()));


  G4VSolid* frontdoor_S = new G4Box("frontdoor_solid", lab68_frontdoor_wood_width/2.0, lab68_wall_thickness/2.0, lab68_frontdoor_wood_height/2.0);
  //G4SubtractionSolid* Main_2b_S= new G4SubtractionSolid("Main_2b_solid", Main_2a_S, frontdoor_S, NO_ROT, G4ThreeVector(lab68_frontdoor_x_coordinate ,-lab68_wall_y/2.0, -(lab68_wall_z-2*lab68_wall_thickness-lab68_frontdoor_glass_height)/2.0));
  G4LogicalVolume* frontdoor_LV = new G4LogicalVolume(frontdoor_S, Wood, "frontdoor");
  frontdoor_PV = new G4PVPlacement(NO_ROT, G4ThreeVector(lab68_frontdoor_glass_width/2.0-lab68_frontdoor_wood_width/2.0 ,0, -lab68_frontdoor_glass_height/2.0+lab68_frontdoor_wood_height/2.0), frontdoor_LV, "Front Wood Door", frontglassdoor_LV, false, 0, fCheckOverlaps);
  frontdoor_LV->SetVisAttributes(G4VisAttributes(G4Colour::Brown()));


  G4VSolid* glasswindow_S = new G4Box("glasswindow_solid", lab68_glasswindow_width/2.0, lab68_wall_thickness/2.0, lab68_glasswindow_height/2.0);
  G4LogicalVolume* glasswindow_LV = new G4LogicalVolume(glasswindow_S, Quartz, "glasswindow");
  glasswindow_PV = new G4PVPlacement(NO_ROT, G4ThreeVector(lab68_frontdoor_wood_width/2.0-0.16*m-lab68_glasswindow_width/2.0, 0, -lab68_frontdoor_wood_height/2.0+1.11*m+lab68_glasswindow_height/2.0), glasswindow_LV, "Front Glass Window", frontdoor_LV, false, 0, fCheckOverlaps);
  glasswindow_LV->SetVisAttributes(G4VisAttributes(G4Colour::Cyan()));


  G4VSolid* reardoor_S = new G4Box("reardoor_solid", lab68_reardoor_width/2.0, lab68_wall_thickness/2.0, lab68_reardoor_height/2.0);
  G4LogicalVolume* reardoor_LV = new G4LogicalVolume(reardoor_S, Wood, "reardoor");
  reardoor_PV = new G4PVPlacement(NO_ROT, G4ThreeVector(lab68_reardoor_x_coordinate ,(lab68_wall_y-lab68_wall_thickness)/2.0, -(lab68_wall_z-2*lab68_wall_thickness-lab68_reardoor_height)/2.0), reardoor_LV, "Rear Wooden Door", LabFloorWall_solid_LV, false, 0, fCheckOverlaps);
  reardoor_LV->SetVisAttributes(G4VisAttributes(G4Colour::Brown()));

  G4double soil_width=2*m;
  G4VSolid* LabFloorExtended_solid_S=  new G4Box("LabFloorExtended_solid", 15.0*m, 15.0*m , soil_width/2.0);
  G4LogicalVolume* LabFloorExtended_solid_LV = new G4LogicalVolume(LabFloorExtended_solid_S, Soil, "LabFloorExtended_solid");
  LabFloorExtended_solid_PV = new G4PVPlacement(turnAlong, G4ThreeVector{lab68_wall_x/2.0,-lab68_wall_y/2.0,lab68_wall_z/2.0}-position_of_origin-G4ThreeVector(0., 0., lab68_wall_z/2.0+soil_width/2.0), LabFloorExtended_solid_LV, "LabFloor_extended", vacuum_solid_LV, false, 0, fCheckOverlaps);
  LabFloorExtended_solid_LV->SetVisAttributes(G4VisAttributes(G4Colour::Brown()));



  G4double extra_concrete_width=2.6*m;
  G4VSolid* Extra_Concrete_Main_S=  new G4Box("LabFloorExtended_Main", 300.0*cm, 15.0*cm , extra_concrete_width/2.0);
  G4VSolid* Extra_Concrete_Hole_S=  new G4Box("LabFloorExtended_Hole", 150.0*cm, 15.0*cm+10*cm , extra_concrete_width/2.0+30*cm);
  G4SubtractionSolid* Extra_Concrete_solid_S= new G4SubtractionSolid("Extra_Concrete_solid", Extra_Concrete_Main_S, Extra_Concrete_Hole_S, NO_ROT, G4ThreeVector(300*cm-140*cm,0., 0.));
  G4LogicalVolume* Extra_Concrete_solid_LV = new G4LogicalVolume(Extra_Concrete_solid_S, Concrete, "Extra_Concrete_solid");
  //G4LogicalVolume* Extra_Concrete_solid_LV = new G4LogicalVolume(Extra_Concrete_Main_S, Concrete, "Extra_Concrete_solid");
  new G4PVPlacement(turnAlong, G4ThreeVector{lab68_wall_x/2.0,-lab68_wall_y/2.0,lab68_wall_z/2.0}-position_of_origin-G4ThreeVector(0., -lab68_wall_y/2.0-lab68_wall_thickness, lab68_wall_z/2.0-extra_concrete_width/2.0), Extra_Concrete_solid_LV, "Extra_Concrete", vacuum_solid_LV, false, 0, fCheckOverlaps);
  Extra_Concrete_solid_LV->SetVisAttributes(G4VisAttributes(G4Colour::Brown()));


  //Insulation but this is actually a surface to see the neutrons coming out of the concrete and borated water
  G4VSolid* Insulation_S = new G4Box("Insulation", Water_cylindercal_can_radius_x/2.0, delta/2.0, (Water_cylindercal_can_height+ConcreteSupport_height)/2.);
  G4LogicalVolume* Insulation_LV = new G4LogicalVolume(Insulation_S, Vacuum, "Insulation");
  Insulation_PV = new G4PVPlacement(NO_ROT, G4ThreeVector(0., fFilterCellSpacing-colimator_length-3*delta/2.0, (Water_cylindercal_can_height-ConcreteSupport_height)/2 - DT_Ti_T_location - Insulation_Thickness), Insulation_LV, "Insulation", vacuum_solid_LV, false, 0, fCheckOverlaps);
  Insulation_LV->SetVisAttributes(G4VisAttributes(G4Colour::Yellow()));


///Lab Ends///////////
////////////////////////////******************///////////////////////////////////////////


////Fridge_Begins///////
///////////////////////////*******************///////////////////////////////////////////
//DilutionUnit contains superfluid Helium
G4VSolid* DilutionUnit_S = new G4Tubs( "DilutionUnit", zeroRadius, DilutionUnit_Radius, (DilutionUnit_Height /2.0), startAngle, spanningAngle);
G4LogicalVolume *DilutionUnit_LV = new G4LogicalVolume( DilutionUnit_S, Helium, "DilutionUnit" );
//G4LogicalVolume *DilutionUnit_LV = new G4LogicalVolume( DilutionUnit_S, Silicon, "DilutionUnit" );
//G4LogicalVolume *DilutionUnit_LV = new G4LogicalVolume( DilutionUnit_S, Diamond, "DilutionUnit" );
//G4LogicalVolume *DilutionUnit_LV = new G4LogicalVolume( DilutionUnit_S, Germanium, "DilutionUnit" );
DilutionUnit_PV = new G4PVPlacement( NO_ROT, G4ThreeVector(0,0,0),DilutionUnit_LV, "helium", vacuum_solid_LV, false, 0, fCheckOverlaps);
//DilutionUnit_LV->SetVisAttributes(G4VisAttributes(G4Colour::Green()));
DilutionUnit_LV->SetVisAttributes(G4VisAttributes(G4Colour::Blue()));


G4VSolid* DilutionUnit_Aluminum_S = new G4Tubs( "DilutionUnit", DilutionUnit_Radius, DilutionUnit_Radius+2.0*cm, (DilutionUnit_Height /2.0)+0.5*cm, startAngle, spanningAngle);
G4LogicalVolume *DilutionUnit_Aluminum_LV = new G4LogicalVolume( DilutionUnit_Aluminum_S, Aluminum, "DilutionAluminumUnit" );
new G4PVPlacement( NO_ROT, G4ThreeVector(0,0,0.5*cm),DilutionUnit_Aluminum_LV, "Aluminum", vacuum_solid_LV, false, 0, fCheckOverlaps);
DilutionUnit_Aluminum_LV->SetVisAttributes(G4VisAttributes(G4Colour::Green()));


//Dilution Chamber that holds the superfluid Helium
G4double nedges[7]=  {-DilutionUnit_Height /2.0-DilutionChamber_bottomplate_thick,
                         -(DilutionUnit_Height /2.0),-(DilutionUnit_Height /2.0),
                         0.0,DilutionUnit_Height/2.0+DilutionChamber_Height,DilutionUnit_Height/2.0+DilutionChamber_Height,
                         DilutionUnit_Height/2.0+DilutionChamber_Height+DilutionChamber_upperplate_thick};

G4double innerradius[7]= {0.0, 0.0, DilutionChamber_Radius ,DilutionChamber_Radius ,  DilutionChamber_Radius, 0.0, 0.0 };
G4double outerradius[7]= {DilutionChamber_Radius+DilutionChamber_Width, DilutionChamber_Radius+DilutionChamber_Width,
                          DilutionChamber_Radius+DilutionChamber_Width,
                          DilutionChamber_Radius+DilutionChamber_Width, DilutionChamber_Radius+DilutionChamber_Width, DilutionChamber_UpperPart_Radius
                          , DilutionChamber_UpperPart_Radius};


G4ThreeVector position_DilutionChamber = G4ThreeVector(0, 0, 0);

G4Polycone* DilutionChamber_S = new G4Polycone("DilutionChamber", startAngle, spanningAngle, 7, nedges, innerradius, outerradius);
G4LogicalVolume*  DilutionChamber_LV= new G4LogicalVolume(DilutionChamber_S, Copper, "DilutionChamber");
DilutionChamber_PV = new G4PVPlacement(NO_ROT, position_DilutionChamber , DilutionChamber_LV, "DilutionChamber", vacuum_solid_LV, false, 0, fCheckOverlaps);
DilutionChamber_LV->SetVisAttributes(G4VisAttributes(G4Colour(1.,0.5,0.)));


G4double CPD_height=1*mm;
G4double CPD_Radius=38*mm;


//detector
G4Tubs* CPDS
  = new G4Tubs("CPDS",0,CPD_Radius,CPD_height/2.0, 0.*deg, 360.*deg);
G4LogicalVolume* CPDLV
  = new G4LogicalVolume(CPDS, Silicon
, "CPDLV",0,0,0);
 new G4PVPlacement(0,               // no rotation
                  G4ThreeVector(0,0,CPD_height/2.0+4*cm), // at (x,y,z)
                  CPDLV,       // its logical volume
                  "CPD",       // its name
                  vacuum_solid_LV,         // its mother  volume
                  false,           // no boolean operations
                  0,               // copy number
                  fCheckOverlaps); // checking overlaps
CPDLV->SetVisAttributes(G4VisAttributes(G4Colour::Yellow()));




//MixingPlate
G4VSolid* MixingPlate_S = new G4Tubs( "MixingPlate", zeroRadius, MixingPlate_Radius, (MixingPlate_Thickness /2.0), startAngle, spanningAngle);
G4LogicalVolume *MixingPlate_LV = new G4LogicalVolume( MixingPlate_S, Copper, "MixingPlate" );
MixingPlate_PV = new G4PVPlacement( NO_ROT, G4ThreeVector(0, 0, MixingPlate_z),MixingPlate_LV, "MixingPlate", vacuum_solid_LV, false, 0, fCheckOverlaps);
MixingPlate_LV->SetVisAttributes(G4VisAttributes(G4Colour(1.,0.5,0.)));

//ColdPlate2
G4VSolid* ColdPlate2_S = new G4Tubs( "ColdPlate2", zeroRadius, ColdPlate2_Radius, (ColdPlate2_Thickness /2.0), startAngle, spanningAngle);
G4LogicalVolume *ColdPlate2_LV = new G4LogicalVolume( ColdPlate2_S, Copper, "ColdPlate2" );
ColdPlate2_PV = new G4PVPlacement( NO_ROT, G4ThreeVector(0, 0, MixingPlate_z+ColdPlate2_z),ColdPlate2_LV, "ColdPlate2", vacuum_solid_LV, false, 0, fCheckOverlaps);
ColdPlate2_LV->SetVisAttributes(G4VisAttributes(G4Colour(1.,0.5,0.)));

//ColdPlate1
G4VSolid* ColdPlate1_S = new G4Tubs( "ColdPlate1", zeroRadius, ColdPlate1_Radius, (ColdPlate1_Thickness /2.0), startAngle, spanningAngle);
G4LogicalVolume *ColdPlate1_LV = new G4LogicalVolume( ColdPlate1_S, Copper, "ColdPlate1" );
ColdPlate1_PV = new G4PVPlacement( NO_ROT, G4ThreeVector(0, 0, MixingPlate_z+ColdPlate2_z+ColdPlate1_z),ColdPlate1_LV, "ColdPlate1", vacuum_solid_LV, false, 0, fCheckOverlaps);
ColdPlate1_LV->SetVisAttributes(G4VisAttributes(G4Colour(1.,0.5,0.)));

//OneKPlate
G4VSolid* OneKPlate_S = new G4Tubs( "OneKPlate", zeroRadius, OneKPlate_Radius, (OneKPlate_Thickness /2.0), startAngle, spanningAngle);
G4LogicalVolume *OneKPlate_LV = new G4LogicalVolume( OneKPlate_S, Copper, "OneKPlate" );
OneKPlate_PV = new G4PVPlacement( NO_ROT, G4ThreeVector(0, 0, MixingPlate_z+ColdPlate2_z+ColdPlate1_z+OneKPlate_z),OneKPlate_LV, "OneKPlate", vacuum_solid_LV, false, 0, fCheckOverlaps);
OneKPlate_LV->SetVisAttributes(G4VisAttributes(G4Colour(1.,0.5,0.)));

G4double z[4]=  {-OneKShield_Width, 0.0, 0.0, OneKShield_Height};
G4double ri[4]= {0.0, 0.0, OneKShield_Radius ,  OneKShield_Radius };
G4double ro[4]= {OneKShield_Radius+OneKShield_Width, OneKShield_Radius+OneKShield_Width, OneKShield_Radius+OneKShield_Width, OneKShield_Radius+OneKShield_Width};
G4ThreeVector position_OneKShield = G4ThreeVector(0, 0, MixingPlate_z+ColdPlate2_z+ColdPlate1_z+OneKPlate_z) + G4ThreeVector(0, 0, -OneKPlate_Thickness/2-OneKShield_Height);

G4Polycone* OneKShield_S = new G4Polycone("OneKShield", startAngle, spanningAngle, 4, z, ri, ro);
G4LogicalVolume*  OneKShield_LV= new G4LogicalVolume(OneKShield_S, Copper, "OneKShield");
//G4LogicalVolume*  OneKShield_LV= new G4LogicalVolume(OneKShield_S, Aluminum, "OneKShield");
OneKShield_PV = new G4PVPlacement(NO_ROT, position_OneKShield , OneKShield_LV, "OneKShield", vacuum_solid_LV, false, 0, fCheckOverlaps);
OneKShield_LV->SetVisAttributes(G4VisAttributes(G4Colour(1.,0.5,0.)));

//FourKPlate
G4VSolid* FourKPlate_S = new G4Tubs( "FourKPlate", zeroRadius, FourKPlate_Radius, (FourKPlate_Thickness/2.0), startAngle, spanningAngle);
G4LogicalVolume *FourKPlate_LV = new G4LogicalVolume( FourKPlate_S, Copper, "FourKPlate" );
FourKPlate_PV = new G4PVPlacement( NO_ROT, G4ThreeVector(0, 0, MixingPlate_z+ColdPlate2_z+ColdPlate1_z+OneKPlate_z+FourKPlate_z),FourKPlate_LV, "FourKPlate", vacuum_solid_LV, false, 0, fCheckOverlaps);
FourKPlate_LV->SetVisAttributes(G4VisAttributes(G4Colour(1.,0.5,0.)));


G4double z1[4]=  {-FourKShield_Width, 0.0, 0.0, FourKShield_Height};
G4double ri1[4]= {0.0, 0.0, FourKShield_Radius ,  FourKShield_Radius };
G4double ro1[4]= {FourKShield_Radius+FourKShield_Width, FourKShield_Radius+FourKShield_Width, FourKShield_Radius+FourKShield_Width, FourKShield_Radius+FourKShield_Width};
G4ThreeVector position_FourKShield = G4ThreeVector(0, 0, MixingPlate_z+ColdPlate2_z+ColdPlate1_z+OneKPlate_z+FourKPlate_z) + G4ThreeVector(0, 0, -FourKPlate_Thickness/2-FourKShield_Height);

G4Polycone* FourKShield_S = new G4Polycone("FourKShield", startAngle, spanningAngle, 4, z1, ri1, ro1);
G4LogicalVolume*  FourKShield_LV= new G4LogicalVolume(FourKShield_S, Copper, "FourKShield");
//G4LogicalVolume*  FourKShield_LV= new G4LogicalVolume(FourKShield_S, Aluminum, "FourKShield");
FourKShield_PV = new G4PVPlacement(NO_ROT, position_FourKShield , FourKShield_LV, "FourKShield", vacuum_solid_LV, false, 0, fCheckOverlaps);
FourKShield_LV->SetVisAttributes(G4VisAttributes(G4Colour(1.,0.5,0.)));


//SeventyKPlate
G4VSolid* SeventyKPlate_S = new G4Tubs( "SeventyKPlate", zeroRadius, SeventyKPlate_Radius, (SeventyKPlate_Thickness /2.0), startAngle, spanningAngle);
G4LogicalVolume *SeventyKPlate_LV = new G4LogicalVolume( SeventyKPlate_S, Copper, "SeventyKPlate" );
SeventyKPlate_PV = new G4PVPlacement( NO_ROT, G4ThreeVector(0, 0, MixingPlate_z+ColdPlate2_z+ColdPlate1_z+OneKPlate_z+FourKPlate_z+SeventyKPlate_z),SeventyKPlate_LV, "SeventyKPlate", vacuum_solid_LV, false, 0, fCheckOverlaps);
SeventyKPlate_LV->SetVisAttributes(G4VisAttributes(G4Colour(1.,0.5,0.)));


G4double z2[4]=  {-SeventyKShield_Width, 0.0, 0.0, SeventyKShield_Height};
G4double ri2[4]= {0.0, 0.0, SeventyKShield_Radius ,  SeventyKShield_Radius };
G4double ro2[4]= {SeventyKShield_Radius+SeventyKShield_Width, SeventyKShield_Radius+SeventyKShield_Width, SeventyKShield_Radius+SeventyKShield_Width, SeventyKShield_Radius+SeventyKShield_Width};
G4ThreeVector position_SeventyKShield = G4ThreeVector(0, 0, MixingPlate_z+ColdPlate2_z+ColdPlate1_z+OneKPlate_z+FourKPlate_z+SeventyKPlate_z) + G4ThreeVector(0, 0, -SeventyKPlate_Thickness/2-SeventyKShield_Height);

G4Polycone* SeventyKShield_S = new G4Polycone("SeventyKShield", startAngle, spanningAngle, 4, z2, ri2, ro2);
G4LogicalVolume*  SeventyKShield_LV= new G4LogicalVolume(SeventyKShield_S, Copper, "SeventyKShield");
//G4LogicalVolume*  SeventyKShield_LV= new G4LogicalVolume(SeventyKShield_S, Aluminum, "SeventyKShield");
SeventyKShield_PV = new G4PVPlacement(NO_ROT, position_SeventyKShield , SeventyKShield_LV, "SeventyKShield", vacuum_solid_LV, false, 0, fCheckOverlaps);
SeventyKShield_LV->SetVisAttributes(G4VisAttributes(G4Colour(1.,0.5,0.)));;


//OVC
G4double z3[4]=  {-OVCShield_Width, 0.0, 0.0, OVCShield_Height};
G4double ri3[4]= {0.0, 0.0, OVCShield_Radius ,  OVCShield_Radius };
G4double ro3[4]= {OVCShield_Radius+OVCShield_Width, OVCShield_Radius+OVCShield_Width, OVCShield_Radius+OVCShield_Width, OVCShield_Radius+OVCShield_Width};
G4ThreeVector position_OVCShield = G4ThreeVector(0, 0, MixingPlate_z+ColdPlate2_z+ColdPlate1_z+OneKPlate_z+FourKPlate_z+SeventyKPlate_z+OVC_z) + G4ThreeVector(0, 0,-OVCShield_Height);

G4Polycone* OVCShield_S = new G4Polycone("OVCShield", startAngle, spanningAngle, 4, z3, ri3, ro3);
G4LogicalVolume*  OVCShield_LV= new G4LogicalVolume(OVCShield_S, Aluminum, "OVCShield");
OVCShield_PV = new G4PVPlacement(NO_ROT, position_OVCShield , OVCShield_LV, "OVCShield", vacuum_solid_LV, false, 0, fCheckOverlaps);
OVCShield_LV->SetVisAttributes(G4VisAttributes(G4Colour(G4Colour::Cyan())));
//OVCShield_LV->SetVisAttributes(G4VisAttributes::Invisible);


// Lead shield around the OVC to block the gamma:

//dimension main semicrcular lead
G4double thickness_Lead=17*cm;
G4double height_Lead=50*cm;


//lead shield
G4double zposition_OVC= 47*cm;
G4double z4[4]=  {-zposition_OVC-OVCShield_Width-thickness_Lead, -zposition_OVC-OVCShield_Width, -zposition_OVC-OVCShield_Width, height_Lead};
G4double ri4[4]= {0.0, 0.0, OVCShield_Radius + OVCShield_Width ,  OVCShield_Radius + OVCShield_Width };
G4double ro4[4]= {OVCShield_Radius + OVCShield_Width + thickness_Lead, OVCShield_Radius + OVCShield_Width + thickness_Lead, OVCShield_Radius + OVCShield_Width + thickness_Lead, OVCShield_Radius + OVCShield_Width + thickness_Lead};

////G4Tubs* Shielding_Lead_S = new G4Tubs("Shielding_Lead_solid2", OVCShield_Radius + OVCShield_Width, OVCShield_Radius + OVCShield_Width + thickness_Lead, height_Lead/2.0 ,startAngle, spanningAngle/2.0);
//G4Polycone* Shielding_Lead_S = new G4Polycone("Shielding_Lead", startAngle, spanningAngle/2.0, 4, z4, ri4, ro4);
//G4Tubs* hole_S2 = new G4Tubs("hole_solid2", 0.0 , 5.0/2.0*cm, thickness_Lead/2.0 + 2.0*cm  ,startAngle, spanningAngle);
//G4SubtractionSolid* BucketShielding_Lead_S= new G4SubtractionSolid("BucketShielding_Lead_S", Shielding_Lead_S, hole_S2, turnAlongX, G4ThreeVector{0,(OVCShield_Radius + OVCShield_Width) + thickness_Lead/2.0,0});
//G4LogicalVolume*  BucketShielding_Lead_LV= new G4LogicalVolume(BucketShielding_Lead_S, Lead, "BucketShielding_Lead");
//BucketShielding_Lead_PV = new G4PVPlacement(NO_ROT, G4ThreeVector{0,0,0}, BucketShielding_Lead_LV, "BucketShielding_Lead",  vacuum_solid_LV, false, 0, true);
//BucketShielding_Lead_LV->SetVisAttributes(G4VisAttributes(G4Colour(G4Colour::Blue())));



//dimension cubical lead
G4double cubical_thickness_Lead=24*cm;//25*cm
G4double cubical_side_length_Lead=30*cm;
G4double cubical_height_Lead_up=60*cm;
G4double cubical_height_Lead_down=50*cm;

G4VSolid* Main_5_S = new G4Box("Main_5_solid",(OVCShield_Radius + OVCShield_Width)/2.0+cubical_side_length_Lead, (cubical_height_Lead_up+cubical_height_Lead_down)/2.0, cubical_thickness_Lead/2.0);
G4VSolid* hole_5_S = new G4Tubs("hole_5_solid", 0 , 5.0/2.0*cm, cubical_thickness_Lead/2.0,startAngle, spanningAngle);

G4SubtractionSolid* BucketShielding_Lead_S= new G4SubtractionSolid("BucketShielding_Lead_S", Main_5_S, hole_5_S, NO_ROT, G4ThreeVector(0., (cubical_height_Lead_up-cubical_height_Lead_down)/2 - DT_Ti_T_location - Insulation_Thickness, 0));
G4LogicalVolume* BucketShielding_Lead_LV = new G4LogicalVolume(BucketShielding_Lead_S, Lead, "BucketShielding_Lead");
BucketShielding_Lead_PV = new G4PVPlacement(turnAlongX, G4ThreeVector(0.,  OVCShield_Radius + OVCShield_Width + cubical_thickness_Lead/2.0, (cubical_height_Lead_up-cubical_height_Lead_down)/2 - DT_Ti_T_location - Insulation_Thickness), BucketShielding_Lead_LV, "BucketShielding_Lead", vacuum_solid_LV, false, 0, fCheckOverlaps);
BucketShielding_Lead_LV->SetVisAttributes(G4VisAttributes(G4Colour(G4Colour::Blue())));
//BucketShielding_Lead_LV->SetVisAttributes(G4VisAttributes::Invisible);


//G4double cubical_thickness_Poly =2.0*cm;

//G4VSolid* Main_4_S = new G4Box("Main_4_solid",(OVCShield_Radius + OVCShield_Width)/2.0+cubical_side_length_Lead, (cubical_height_Lead_up+cubical_height_Lead_down)/2.0, cubical_thickness_Poly/2.0);
//G4VSolid* hole_4_S = new G4Tubs("hole_4_solid", 0 , 5.0/2.0*cm, cubical_thickness_Poly/2.0,startAngle, spanningAngle);

//G4SubtractionSolid* BucketShielding_Poly_S= new G4SubtractionSolid("BucketShielding_Poly_S", Main_4_S, hole_4_S, NO_ROT, G4ThreeVector(0., (cubical_height_Lead_up-cubical_height_Lead_down)/2 - DT_Ti_T_location - Insulation_Thickness, 0));
//G4LogicalVolume* BucketShielding_Poly_LV = new G4LogicalVolume(BucketShielding_Poly_S, Polyethylene, "BucketShielding_Poly");
//new G4PVPlacement(0, G4ThreeVector(0., 0., -cubical_thickness_Lead/2+cubical_thickness_Poly/2.0), BucketShielding_Poly_LV, "BucketShielding_Poly", BucketShielding_Lead_LV, false, 0, fCheckOverlaps);
//BucketShielding_Poly_LV->SetVisAttributes(G4VisAttributes(G4Colour(G4Colour::Green())));




///////////////***********************////////////////////////


  ///Helium cell
  //Iron final  Moderator in the form of cylinder
  //G4VSolid* inner_shield_S = new G4Tubs( "inner_shield", zeroRadius, DilutionUnit_Radius, (DilutionUnit_Height /2.0), startAngle, spanningAngle);
  //G4LogicalVolume *inner_shield_LV = new G4LogicalVolume( inner_shield_S, Helium, "inner_shield" );
  //inner_shield_PV = new G4PVPlacement( NO_ROT, G4ThreeVector(0,0,0),inner_shield_LV, "helium", vacuum_solid_LV, false, 0, fCheckOverlaps);



/*  //G4Polycone
  G4Polycone* first_S = new G4Polycone("first_solid", startAngle, spanningAngle, nbEdges, z, rIn, rOut);
  G4VSolid* second_S = new G4Box("second_solid", SiPMSide/2.0, SiPMSide/2.0, SiPMthickness/2.0);
  G4SubtractionSolid * airlayer_solid_S =  new G4SubtractionSolid ("airlayer_solid", first_S, second_S, NO_ROT, G4ThreeVector(0, 0, -(ScintillatorHeight+SiPMthickness)/2.0));
  G4LogicalVolume* airlayer_solid_LV = new G4LogicalVolume(airlayer_solid_S, Aluminum, "airlayer_solid");
  airlayer_solid_PV = new G4PVPlacement(NO_ROT, G4ThreeVector(0., 0., 0.0), airlayer_solid_LV, "Aluminum_Reflector", vacuum_solid_LV, false, 0, fCheckOverlaps);
*/
   //Second detector
  //Front Polyethylene layer, front is in -ve z axis
  G4VSolid* shielding_lead_S = new G4Tubs("shielding_lead", Inner_Radius, Inner_Radius+ Radial_thickness,(Front_Moderator_Thickness/2.0), startAngle, spanningAngle);
  G4LogicalVolume* shielding_lead_LV = new G4LogicalVolume(shielding_lead_S, Polyethylene, "shielding_lead_solid");
  shielding_lead_PV = new G4PVPlacement(turnAlongX, G4ThreeVector(0., -(second_detector_z-(shieldHeight-Front_Moderator_Thickness)/2.0), 0.), shielding_lead_LV, "2ndTitanium_Reflector_A", vacuum_solid_LV, false, 0, fCheckOverlaps);


  //Back Borated-Polyethylene layer, is in +ve z axis to capture the rest neutrons
  //G4VSolid* moderator_iron_S = new G4Tubs( "moderator_iron", Inner_Radius, Inner_Radius+ Radial_thickness,(BoratedPoly_thickness/2.0), startAngle, spanningAngle);
  //G4LogicalVolume *moderator_iron_LV = new G4LogicalVolume( moderator_iron_S, PolBor10pc, "moderator_iron" );
  //moderator_iron_PV = new G4PVPlacement( NO_ROT, G4ThreeVector(0,0,second_detector_z+(shieldHeight+BoratedPoly_thickness)/2.0),moderator_iron_LV, "Borated_Capturer", vacuum_solid_LV, false, 0, fCheckOverlaps);

  //Back Polyethylene layer, back is in +ve z axis
  G4VSolid* Iron_solid_S = new G4Tubs("Iron_solid", Inner_Radius, Inner_Radius+ Radial_thickness,(Back_Moderator_Thickness/2.0), startAngle, spanningAngle);
  G4LogicalVolume *Iron_solid_LV = new G4LogicalVolume(Iron_solid_S, Polyethylene,"Iron_solid" );
  Iron_solid_PV = new G4PVPlacement( turnAlongX, G4ThreeVector(0,-(second_detector_z+(shieldHeight-Back_Moderator_Thickness)/2.0),0), Iron_solid_LV, "2nd_SiPM_A",vacuum_solid_LV,false, 0, fCheckOverlaps);

  //Acrylic in the middle
  G4VSolid* DT_solid_S = new G4Tubs("DT_solid", Inner_Radius, Inner_Radius+ Radial_thickness,(Mid_Acrylic_thickness/2.0), startAngle, spanningAngle);
  G4LogicalVolume *DT_solid_LV = new G4LogicalVolume(DT_solid_S, Acrylic,"DT_solid" );
  DT_solid_PV = new G4PVPlacement( turnAlongX, G4ThreeVector(0,-(second_detector_z+(shieldHeight-2*Back_Moderator_Thickness-Mid_Acrylic_thickness)/2.0),0), DT_solid_LV, "2nd_Scintillator_A",  vacuum_solid_LV, false, 0, fCheckOverlaps);



  //Front EJ426, placed in Acrylic as its Mother Volume, Front is -ve z axis
  G4VSolid* filter_aluminum_S = new G4Tubs("filter_aluminum_solid", Inner_Radius, Inner_Radius+ Radial_thickness,(EJ426_thickness/2.0), startAngle, spanningAngle);
  G4LogicalVolume* filter_aluminum_LV = new G4LogicalVolume(filter_aluminum_S, EJ4265HD , "filter_aluminum_solid");
  filter_aluminum_PV = new G4PVPlacement(NO_ROT, G4ThreeVector(0., 0., -(Mid_Acrylic_thickness-EJ426_thickness)/2.0), filter_aluminum_LV, "2nd_Leadlayer_A", DT_solid_LV, false, 0, fCheckOverlaps);


  //Back EJ426, placed in Acrylic as its Mother Volume, Back is +ve z axis
  G4VSolid* shield_cap_iron_S = new G4Tubs("Shield_cap_iron", Inner_Radius, Inner_Radius+ Radial_thickness,(EJ426_thickness/2.0), startAngle, spanningAngle);
  G4LogicalVolume *shield_cap_iron_LV = new G4LogicalVolume(shield_cap_iron_S, EJ4265HD,"shield_cap" );
  shield_cap_iron_PV = new G4PVPlacement( NO_ROT, G4ThreeVector(0,0,(Mid_Acrylic_thickness-EJ426_thickness)/2.0), shield_cap_iron_LV, "2nd_FeCap_A", DT_solid_LV, false, 0, fCheckOverlaps );


//First detector, distance between the helium Cell and the Detector is given
G4double first_detector_z =  30.0*cm;//45.0*cm
shielding_lead_PV_2 = new G4PVPlacement(turnAlongX, G4ThreeVector(0., -(first_detector_z-(shieldHeight-Front_Moderator_Thickness)/2.0), 0.), shielding_lead_LV, "1stTitanium_Reflector_A", vacuum_solid_LV, false, 0, fCheckOverlaps);
Iron_solid_PV_2 = new G4PVPlacement( turnAlongX, G4ThreeVector(0,-(first_detector_z+(shieldHeight-Back_Moderator_Thickness)/2.0),0), Iron_solid_LV, "1st_SiPM_A",vacuum_solid_LV,false, 0, fCheckOverlaps);

G4LogicalVolume *DT_solid_LV_2 = new G4LogicalVolume(DT_solid_S, Acrylic,"DT_solid" );
DT_solid_PV_2 = new G4PVPlacement( turnAlongX, G4ThreeVector(0,-(first_detector_z+(shieldHeight-2*Back_Moderator_Thickness-Mid_Acrylic_thickness)/2.0),0), DT_solid_LV_2, "1st_Scintillator_A",  vacuum_solid_LV, false, 0, fCheckOverlaps);

filter_aluminum_PV_2 = new G4PVPlacement(NO_ROT, G4ThreeVector(0., 0., -(Mid_Acrylic_thickness-EJ426_thickness)/2.0), filter_aluminum_LV, "1st_Leadlayer_A", DT_solid_LV_2, false, 0, fCheckOverlaps);
shield_cap_iron_PV_2 = new G4PVPlacement( NO_ROT, G4ThreeVector(0,0,(Mid_Acrylic_thickness-EJ426_thickness)/2.0), shield_cap_iron_LV, "1st_FeCap_A", DT_solid_LV_2, false, 0, fCheckOverlaps );

//third detector, distance between the helium Cell and the Detector is given
G4double third_detector_z =  120.0*cm;
shielding_lead_PV_3 = new G4PVPlacement(turnAlongX, G4ThreeVector(0., -(third_detector_z-(shieldHeight-Front_Moderator_Thickness)/2.0), 0.), shielding_lead_LV, "3rdTitanium_Reflector_A", vacuum_solid_LV, false, 0, fCheckOverlaps);
Iron_solid_PV_3 = new G4PVPlacement( turnAlongX, G4ThreeVector(0,-(third_detector_z+(shieldHeight-Back_Moderator_Thickness)/2.0),0), Iron_solid_LV, "3rd_SiPM_A",vacuum_solid_LV,false, 0, fCheckOverlaps);

G4LogicalVolume *DT_solid_LV_3 = new G4LogicalVolume(DT_solid_S, Acrylic,"DT_solid" );
DT_solid_PV_3 = new G4PVPlacement( turnAlongX, G4ThreeVector(0,-(third_detector_z+(shieldHeight-2*Back_Moderator_Thickness-Mid_Acrylic_thickness)/2.0),0), DT_solid_LV_3, "3rd_Scintillator_A",  vacuum_solid_LV, false, 0, fCheckOverlaps);

filter_aluminum_PV_3 = new G4PVPlacement(NO_ROT, G4ThreeVector(0., 0., -(Mid_Acrylic_thickness-EJ426_thickness)/2.0), filter_aluminum_LV, "3rd_Leadlayer_A", DT_solid_LV_3, false, 0, fCheckOverlaps);
shield_cap_iron_PV_3 = new G4PVPlacement( NO_ROT, G4ThreeVector(0,0,(Mid_Acrylic_thickness-EJ426_thickness)/2.0), shield_cap_iron_LV, "3rd_FeCap_A", DT_solid_LV_3, false, 0, fCheckOverlaps );


/*
//fourth Detector, distance between the helium Cell and the Detector is given


G4double fourth_detector_z = 150.0*cm+shieldHeight/2.0;
//G4double fourth_detector_z = 20.0*cm+shieldHeight/2.0;

//Front Polyethylene layer, front is in -ve z axis
G4VSolid* shielding_lead_S_1 = new G4Tubs("shielding_lead_1", Inner_Radius-10.0*cm, Inner_Radius+ Radial_thickness-10.0*cm,(Front_Moderator_Thickness/2.0), startAngle, spanningAngle);
G4LogicalVolume* shielding_lead_LV_1 = new G4LogicalVolume(shielding_lead_S_1, Polyethylene, "shielding_lead_solid_1");
shielding_lead_PV_1 = new G4PVPlacement(turnAlongX, G4ThreeVector(0., -(fourth_detector_z-(shieldHeight-Front_Moderator_Thickness)/2.0), 0.), shielding_lead_LV_1, "4th_Titanium_Reflector_B", vacuum_solid_LV, false, 0, fCheckOverlaps);



//Back Polyethylene layer, back is in +ve z axis
G4VSolid* Iron_solid_S_1 = new G4Tubs("Iron_solid_1", Inner_Radius-10.0*cm, Inner_Radius+ Radial_thickness-10.0*cm,(Back_Moderator_Thickness/2.0), startAngle, spanningAngle);
G4LogicalVolume *Iron_solid_LV_1 = new G4LogicalVolume(Iron_solid_S_1, Polyethylene,"Iron_solid_1" );
Iron_solid_PV_1= new G4PVPlacement( turnAlongX, G4ThreeVector(0,-(fourth_detector_z+(shieldHeight-Back_Moderator_Thickness)/2.0),0), Iron_solid_LV_1, "4th_SiPM_B",vacuum_solid_LV,false, 0, fCheckOverlaps);

//Acrylic in the middle
G4VSolid* DT_solid_S_1 = new G4Tubs("DT_solid_1", Inner_Radius-10.0*cm, Inner_Radius+ Radial_thickness-10.0*cm,(Mid_Acrylic_thickness/2.0), startAngle, spanningAngle);
G4LogicalVolume *DT_solid_LV_1 = new G4LogicalVolume(DT_solid_S_1, Acrylic,"DT_solid_1" );
DT_solid_PV_1 = new G4PVPlacement( turnAlongX, G4ThreeVector(0,-(fourth_detector_z+(shieldHeight-2*Back_Moderator_Thickness-Mid_Acrylic_thickness)/2.0),0), DT_solid_LV_1, "4th_Scintillator_B",  vacuum_solid_LV, false, 0, fCheckOverlaps);



//Front EJ426, placed in Acrylic as its Mother Volume, Front is -ve z axis
G4VSolid* filter_aluminum_S_1 = new G4Tubs("filter_aluminum_solid_1", Inner_Radius-10.0*cm, Inner_Radius+ Radial_thickness-10.0*cm,(EJ426_thickness/2.0), startAngle, spanningAngle);
G4LogicalVolume* filter_aluminum_LV_1 = new G4LogicalVolume(filter_aluminum_S_1, EJ4265HD , "filter_aluminum_solid_1");
filter_aluminum_PV_1 = new G4PVPlacement(NO_ROT, G4ThreeVector(0., 0., -(Mid_Acrylic_thickness-EJ426_thickness)/2.0), filter_aluminum_LV_1, "4th_Leadlayer_B", DT_solid_LV_1, false, 0, fCheckOverlaps);


//Back EJ426, placed in Acrylic as its Mother Volume, Back is +ve z axis
G4VSolid* shield_cap_iron_S_1 = new G4Tubs("Shield_cap_iron_1", Inner_Radius-10.0*cm, Inner_Radius+ Radial_thickness-10.0*cm,(EJ426_thickness/2.0), startAngle, spanningAngle);
G4LogicalVolume *shield_cap_iron_LV_1 = new G4LogicalVolume(shield_cap_iron_S_1, EJ4265HD,"shield_cap_1" );
shield_cap_iron_PV_1 = new G4PVPlacement( NO_ROT, G4ThreeVector(0,0,(Mid_Acrylic_thickness-EJ426_thickness)/2.0), shield_cap_iron_LV_1, "4th_FeCap_B", DT_solid_LV_1, false, 0, fCheckOverlaps );

//fifth Detector, distance between the helium Cell and the Detector is given
G4double fifth_detector_z = 250.0*cm+shieldHeight/2.0;

shielding_lead_PV_1_5 = new G4PVPlacement(turnAlongX, G4ThreeVector(0., -(fifth_detector_z-(shieldHeight-Front_Moderator_Thickness)/2.0), 0.), shielding_lead_LV_1, "5th_Titanium_Reflector_B", vacuum_solid_LV, false, 0, fCheckOverlaps);
Iron_solid_PV_1_5= new G4PVPlacement( turnAlongX, G4ThreeVector(0,-(fifth_detector_z+(shieldHeight-Back_Moderator_Thickness)/2.0),0), Iron_solid_LV_1, "5th_SiPM_B",vacuum_solid_LV,false, 0, fCheckOverlaps);
G4LogicalVolume *DT_solid_LV_1_5 = new G4LogicalVolume(DT_solid_S_1, Acrylic,"DT_solid_1" );
DT_solid_PV_1_5 = new G4PVPlacement( turnAlongX, G4ThreeVector(0,-(fifth_detector_z+(shieldHeight-2*Back_Moderator_Thickness-Mid_Acrylic_thickness)/2.0),0), DT_solid_LV_1_5, "5th_Scintillator_B",  vacuum_solid_LV, false, 0, fCheckOverlaps);
filter_aluminum_PV_1_5 = new G4PVPlacement(NO_ROT, G4ThreeVector(0., 0., -(Mid_Acrylic_thickness-EJ426_thickness)/2.0), filter_aluminum_LV_1, "5th_Leadlayer_B", DT_solid_LV_1_5, false, 0, fCheckOverlaps);
shield_cap_iron_PV_1_5 = new G4PVPlacement( NO_ROT, G4ThreeVector(0,0,(Mid_Acrylic_thickness-EJ426_thickness)/2.0), shield_cap_iron_LV_1, "5th_FeCap_B", DT_solid_LV_1_5, false, 0, fCheckOverlaps );

//sixth Detector, distance between the helium Cell and the Detector is given
G4double sixth_detector_z = 400.0*cm+shieldHeight/2.0;

shielding_lead_PV_1_6 = new G4PVPlacement(turnAlongX, G4ThreeVector(0., -(sixth_detector_z-(shieldHeight-Front_Moderator_Thickness)/2.0), 0.), shielding_lead_LV_1, "6th_Titanium_Reflector_B", vacuum_solid_LV, false, 0, fCheckOverlaps);
Iron_solid_PV_1_6= new G4PVPlacement( turnAlongX, G4ThreeVector(0,-(sixth_detector_z+(shieldHeight-Back_Moderator_Thickness)/2.0),0), Iron_solid_LV_1, "6th_SiPM_B",vacuum_solid_LV,false, 0, fCheckOverlaps);
G4LogicalVolume *DT_solid_LV_1_6 = new G4LogicalVolume(DT_solid_S_1, Acrylic,"DT_solid_1" );
DT_solid_PV_1_6 = new G4PVPlacement( turnAlongX, G4ThreeVector(0,-(sixth_detector_z+(shieldHeight-2*Back_Moderator_Thickness-Mid_Acrylic_thickness)/2.0),0), DT_solid_LV_1_6, "6th_Scintillator_B",  vacuum_solid_LV, false, 0, fCheckOverlaps);
filter_aluminum_PV_1_6 = new G4PVPlacement(NO_ROT, G4ThreeVector(0., 0., -(Mid_Acrylic_thickness-EJ426_thickness)/2.0), filter_aluminum_LV_1, "6th_Leadlayer_B", DT_solid_LV_1_6, false, 0, fCheckOverlaps);
shield_cap_iron_PV_1_6 = new G4PVPlacement( NO_ROT, G4ThreeVector(0,0,(Mid_Acrylic_thickness-EJ426_thickness)/2.0), shield_cap_iron_LV_1, "6th_FeCap_B", DT_solid_LV_1_6, false, 0, fCheckOverlaps );

*/


//
// Visualization attributes
//
  vacuum_solid_LV->SetVisAttributes(G4VisAttributes::Invisible);
  //inner_shield_LV->SetVisAttributes(G4VisAttributes::Invisible);

  G4VisAttributes* test_vis = new G4VisAttributes(G4Colour(0.0,1.0,0.0,0.5));  //used in verification of the geometry
  //G4VisAttributes* iron_vis = new G4VisAttributes(G4Colour(1.0,0.0,0.0,0.5));
  G4VisAttributes* aluminum_vis = new G4VisAttributes(G4Colour(1.0,0.0,0.0,0.5));


  //G4VisAttributes* lead_vis = new G4VisAttributes(G4Colour(0.0,0.0,1.0,0.5));
  G4VisAttributes* helium_vis = new G4VisAttributes(G4Colour(1.0,1.0,0.0,0.5));
  G4VisAttributes* lead_vis = new G4VisAttributes(G4Colour(1.0,0.0,0.0,0.5));
  G4VisAttributes* silicon_vis = new G4VisAttributes(G4Colour(0.0,1.0,0.0,0.5));
  G4VisAttributes* ej_254_5pc_vis = new G4VisAttributes(G4Colour(0.0,0.0,1.0,0.5));
  G4VisAttributes* LithiumIodide_vis = new G4VisAttributes(G4Colour(0.6,0.5,1.0,0.5));
  G4VisAttributes* air_vis = new G4VisAttributes(G4Colour(1.0,0.5,0.5,0.5));
  G4VisAttributes* EJ230_vis = new G4VisAttributes(G4Colour(0.0,1.0,1.0,0.5));
  G4VisAttributes* EJ4265HD_vis = new G4VisAttributes(G4Colour(0.0,0.0,1.0,0.5));


  //2nd Detector of type A
  //inner_shield_LV->SetVisAttributes(helium_vis);
  shielding_lead_LV->SetVisAttributes(lead_vis);

  //moderator_iron_LV->SetVisAttributes(LithiumIodide_vis);

  Iron_solid_LV->SetVisAttributes(lead_vis);

  DT_solid_LV->SetVisAttributes(silicon_vis);

  //DT_solid_LV_1->SetVisAttributes(silicon_vis);

  filter_aluminum_LV->SetVisAttributes(EJ4265HD_vis);
  shield_cap_iron_LV->SetVisAttributes(EJ4265HD_vis);//Design A
  //shielding_lead_LV->SetVisAttributes(G4VisAttributes::Invisible);


/*
//fourth detector of type B
shielding_lead_LV_1->SetVisAttributes(lead_vis);

//moderator_iron_LV->SetVisAttributes(LithiumIodide_vis);

Iron_solid_LV_1->SetVisAttributes(lead_vis);

DT_solid_LV_1->SetVisAttributes(silicon_vis);

filter_aluminum_LV_1->SetVisAttributes(EJ4265HD_vis);
shield_cap_iron_LV_1->SetVisAttributes(EJ4265HD_vis);//Design A
*/

//1st_Detector of type A
DT_solid_LV_2->SetVisAttributes(silicon_vis);
//3rd_Detector of type A
DT_solid_LV_3->SetVisAttributes(silicon_vis);

/*
//5th_Detector of type B
DT_solid_LV_1_5->SetVisAttributes(silicon_vis);

//6th_Detector of type B
DT_solid_LV_1_6->SetVisAttributes(silicon_vis);

*/
  /////shielding_lead_LV->SetVisAttributes(lead_vis);//Design D
  ///////shielding_lead_LV->SetVisAttributes(lead_vis);//Design E

  ///////moderator_iron_1_LV->SetVisAttributes(iron_vis);


  //
  // Always return the physical World
  //
  return vacuum_solid_PV;
}



//method SetPolyHeight is defined here
void IronFilterDetectorConstruction::SetPolyHeight(G4double ival)
{
  if (ival < 1)
    { G4cout << "\n --->warning from SetfPolyHeight: "
             << ival << " must be at least 1. Command refused" << G4endl;
      return;
    }
  fPolyHeight = ival;
}


//method SetFilterSpacing is defined here
void IronFilterDetectorConstruction::SetFilterSpacing(G4double ival)
{
  if (ival < 1)
    { G4cout << "\n --->warning from SetfFilterSpacing: "
             << ival << " must be at least 1. Command refused" << G4endl;
      return;
    }
  fFilterSpacing = ival;
}

//method SetMultiplierLeadRadius is defined here
void IronFilterDetectorConstruction::SetMultiplierLeadRadius(G4double ival)
{
  if (ival < 1)
    { G4cout << "\n --->warning from SetfMultiplierLeadRadius: "
             << ival << " must be at least 1. Command refused" << G4endl;
      return;
    }
  fMultiplierLeadRadius = ival;
}
//method SetModeratorAluminumRadius is defined here
void IronFilterDetectorConstruction::SetModeratorAluminumRadius(G4double ival)
{
  if (ival < 1)
    { G4cout << "\n --->warning from SetfModeratorAluminumRadius: "
             << ival << " must be at least 1. Command refused" << G4endl;
      return;
    }
  fModeratorAluminumRadius = ival;
}
//method SetMultiplierLeadHeightRear is defined here
void IronFilterDetectorConstruction::SetMultiplierLeadHeightRear(G4double ival)
{
  if (ival < 0)
    { G4cout << "\n --->warning from SetfMultiplierLeadHeightRear: "
             << ival << " must be at least 0. Command refused" << G4endl;
      return;
    }
  fMultiplierLeadHeightRear = ival;
}
//method SetFilterCellSpacing is defined here
void IronFilterDetectorConstruction::SetFilterCellSpacing(G4double ival)
{
  if (ival < 1)
    { G4cout << "\n --->warning from SetfFilterCellSpacing: "
             << ival << " must be at least 1. Command refused" << G4endl;
      return;
    }
  fFilterCellSpacing = ival;
}
//method SetModeratorTitaniumHeight is defined here
void IronFilterDetectorConstruction::SetModeratorTitaniumHeight(G4double ival)
{
  if (ival < 1)
    { G4cout << "\n --->warning from SetfModeratorTitaniumHeight: "
             << ival << " must be at least 1. Command refused" << G4endl;
      return;
    }
  fModeratorTitaniumHeight = ival;
}
//method SetModeratorAluminumHeight is defined here
void IronFilterDetectorConstruction::SetModeratorAluminumHeight(G4double ival)
{
  if (ival < 1)
   { G4cout << "\n --->warning from SetfModeratorAluminumHeight: "
             << ival << " must be at least 1. Command refused" << G4endl;
      return;
    }
  fModeratorAluminumHeight = ival;
}
//method SetMultiplierLeadHeightFront is defined here
void IronFilterDetectorConstruction::SetMultiplierLeadHeightFront(G4double ival)
{
  if (ival < 1)
    { G4cout << "\n --->warning from SetfMultiplierLeadHeightFront: "
             << ival << " must be at least 1. Command refused" << G4endl;
      return;
    }
  fMultiplierLeadHeightFront = ival;
}
//method SetModeratorTitaniumRadius is defined here
void IronFilterDetectorConstruction::SetModeratorTitaniumRadius(G4double ival)
{
  if (ival < 1)
    { G4cout << "\n --->warning from SetfModeratorTitaniumRadius: "
             << ival << " must be at least 1. Command refused" << G4endl;
      return;
    }
  fModeratorTitaniumRadius = ival;
}

void IronFilterDetectorConstruction::SetTestX(G4double ival)
{
  ftestx = ival;
}

void IronFilterDetectorConstruction::SetTestY(G4double ival)
{
  ftesty = ival;
}

void IronFilterDetectorConstruction::SetTestZ(G4double ival)
{
  ftestz = ival;
}
