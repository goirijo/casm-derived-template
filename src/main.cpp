#include <iostream>
#include <casm/CASM_global_definitions.hh>
#include <casm/crystallography/Structure.hh>
#include <casm/crystallography/Niggli.hh>
#include <casm/casm_io/VaspIO.hh>

int main()
{
    /**
     * Let's read a POSCAR file, primitize it, and write it
     */

	// read
	std::string infile = "POSCAR";
	CASM::Structure input(infile);

	// check primitive
	CASM::BasicStructure<CASM::Site> true_prim;
	true_prim.title = input.title;
    	if(!input.is_primitive(true_prim)) {
		std::cout << "Structure is not primitive, finding prim" << std::endl;
        	CASM::Structure tmp(true_prim);
        	CASM::Lattice lat_niggli = canonical_equivalent_lattice(true_prim.lattice(), tmp.point_group(), CASM::TOL);
        	tmp.set_lattice(lat_niggli, CASM::CART);
        	input = tmp;
	} else {
		std::cout << "Structure is primitive" << std::endl;
	}

	// write
	std::string outfile = "POSCAR_out";
	CASM::VaspIO::PrintPOSCAR p(input);
	p.sort();
	CASM::fs::ofstream file;
	file.open(outfile);
	p.print(file);
	file.close();
	
    return 0;
}
