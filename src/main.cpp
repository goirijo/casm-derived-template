#include <iostream>
#include <casm/CASM_global_definitions.hh>
#include <casm/crystallography/Structure.hh>
#include <casm/crystallography/Niggli.hh>
#include <casm/casm_io/VaspIO.hh>
#include "casm/clex/ConfigMapping.hh"
#include "casm/clex/PrimClex.hh"

double structure_map(const CASM::fs::path POS_a, const CASM::fs::path POS_b) {
	// get prim_a and prim_b
	CASM::Structure struct_a(POS_a);
	CASM::BasicStructure<CASM::Site> prim_a;
	struct_a.is_primitive(prim_a);
	CASM::Structure struct_b(POS_b);
	CASM::BasicStructure<CASM::Site> prim_b;
	struct_b.is_primitive(prim_b);
	// make primclex
	CASM::PrimClex pclex(struct_a, CASM::Logging());
	// map
	double WEIGHT = 0.0;    // lattice mapping weight
	double VOL_TOL = 0.5;   // max volume change
	int options = 2; 	// robust
	CASM::ConfigMapper configmapper(pclex, WEIGHT, VOL_TOL, options, CASM::TOL);
	CASM::jsonParser out;
	std::string name;
	std::vector<CASM::Index> best;
	Eigen::Matrix3d cart_op;	
	configmapper.import_structure_occupation(prim_b, name, out, best, cart_op, true);
	double basis = out["best_mapping"]["basis_deformation"].get<double>();
	double lattice = out["best_mapping"]["lattice_deformation"].get<double>();
	return WEIGHT*lattice + (1-WEIGHT)*basis;
}

int main()
{
    /**
     * Let's find the mapping score between two POSCARs
     */
	CASM::fs::path POS_a = "POSCAR_a";
	CASM::fs::path POS_b = "CONTCAR_a";
	std::cout << "Total mapping score: " << structure_map(POS_a, POS_b) << std::endl;
    return 0;
}
