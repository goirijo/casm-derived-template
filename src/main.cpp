#include <iostream>
#include <casm/CASM_global_definitions.hh>
#include <casm/crystallography/Structure.hh>
#include <casm/crystallography/Lattice.hh>
#include <casm/casm_io/VaspIO.hh>
#include <casm/strain/StrainConverter.hh>

void print_pos(const CASM::Structure &struc)
{
    CASM::VaspIO::PrintPOSCAR printer(struc);
    printer.print(std::cout);
}

CASM::Structure make_super_struc(const CASM::Structure &struc, Eigen::Matrix3d trans_mat)
{
    auto mylat_mat = struc.lattice().lat_column_mat();
    CASM::Lattice suplat(trans_mat*mylat_mat);
    return struc.create_superstruc(suplat);
}

CASM::Structure make_super_struc(const CASM::Structure &struc, const CASM::fs::path path)
{
    Eigen::Matrix3d trans_mat;
    CASM::fs::ifstream mat_file(path);
    mat_file >> trans_mat;
    return make_super_struc(struc, trans_mat);
}

CASM::Structure apply_strain(const CASM::Structure &struc, Eigen::Matrix3d dF) //should we remove rotation??
{
    Eigen::Matrix3d I = Eigen::Matrix3d::Identity();
    auto U = CASM::StrainConverter::right_stretch_tensor(dF+I);
    CASM::Lattice strain_lat(U*struc.lattice().lat_column_mat());
    CASM::Structure strain_struc(strain_lat);
    strain_struc.set_basis(struc.basis);
    strain_struc.title = struc.title;
    return strain_struc;
}

CASM::Structure apply_strain(const CASM::Structure &struc, Eigen::VectorXd vec)
{
    Eigen::Matrix3d F;
    F(0,0) = vec(0);
    F(1,1) = vec(1);
    F(2,2) = vec(2);
    F(1,2) = F(2,1) = vec(3);
    F(0,2) = F(2,0) = vec(4);
    F(0,1) = F(1,0) = vec(5);
    return apply_strain(struc,F);
}

int main()
{
    
    //read a pos, write to screen and a file
    CASM::fs::path filepath = "/home/harsha/casm_2x/casm-derived-template/files/Ti2O_hcp"; 
    CASM::Structure mypos(filepath);
    print_pos(mypos);

    //make a supercell and store in a file
    CASM::fs::path trans_mat_path = "/home/harsha/casm_2x/casm-derived-template/files/trans_mat";
    auto super_pos = make_super_struc(mypos, trans_mat_path);
    print_pos(super_pos);

    //apply strain as a matrix and as a vector
    Eigen::Matrix3d dF;
    dF << 0.0, 0.02, 0.01,
        -0.01, -0.01, 0.0,
        0.0, -0.01, 0.02;
    auto strain_pos = apply_strain(mypos, dF);
    print_pos(strain_pos);

    Eigen::VectorXd vect(6);
    vect << 0.0,0.01,0.03,-0.02,-0.01,0.02;
    auto strain_pos2 = apply_strain(mypos, vect);
    print_pos(strain_pos2);
    
    return 0;
}
