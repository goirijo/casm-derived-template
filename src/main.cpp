#include "casm/clex/ConfigMapping.hh"
#include "casm/clex/PrimClex.hh"
#include <casm/CASM_global_definitions.hh>
#include <casm/casm_io/VaspIO.hh>
#include <casm/crystallography/Niggli.hh>
#include <casm/crystallography/Structure.hh>
#include <iostream>

CASM::Structure get_primitive(const CASM::Structure& superstruc);

double structure_map(
    const CASM::fs::path POS_a, const CASM::fs::path POS_b, double weight = 0.0, double vol_tol = 0.5, tol = CASM::TOL)
{
    // get prim_a and prim_b
    CASM::Structure struct_a(POS_a);
    CASM::BasicStructure<CASM::Site> prim_a;
    struct_a.is_primitive(prim_a);
    CASM::Structure struct_b(POS_b);
    CASM::BasicStructure<CASM::Site> prim_b;
    struct_b.is_primitive(prim_b);
    // make primclex
    CASM::PrimClex pclex(CASM::Structure(prim_a), CASM::Logging());
    // map
    int options = 2; // robust
    CASM::ConfigMapper configmapper(pclex, weight, vol_tol, options, tol);
    CASM::jsonParser out;
    std::string name;
    std::vector<CASM::Index> best;
    Eigen::Matrix3d cart_op;
    configmapper.import_structure_occupation(prim_b, name, out, best, cart_op, true);
    double basis = out["best_mapping"]["basis_deformation"].get<double>();
    double lattice = out["best_mapping"]["lattice_deformation"].get<double>();
    return weight * lattice + (1 - weight) * basis;
}

double structure_score(const CASM::Structure& map_reference_struc,
                       const CASM::Structure& mappable_struc,
                       double weight = 0.0,
                       double vol_tol = 0.5,
                       tol = CASM::TOL)
{
    auto ref_prim=get_primitive(map_reference_struc);

    CASM::PrimClex pclex(ref_prim);

    // map
    int options = 2; // robust
    CASM::ConfigMapper configmapper(pclex, weight, vol_tol, options, tol);
    CASM::jsonParser out;
    std::string name;
    std::vector<CASM::Index> best;
    Eigen::Matrix3d cart_op;
    configmapper.import_structure_occupation(mappable_struc, name, out, best, cart_op, true);
    double basis = out["best_mapping"]["basis_deformation"].get<double>();
    double lattice = out["best_mapping"]["lattice_deformation"].get<double>();
    return weight * lattice + (1 - weight) * basis;
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
