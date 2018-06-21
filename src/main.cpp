#include <iostream>
#include <casm/CASM_global_definitions.hh>
#include <casm/crystallography/Structure.hh>
#include <casm/casm_io/VaspIO.hh>

int main()
{
    /**
     * Let's read and write a POSCAR file
     */

	// read
	std::string infile = "POSCAR";
	CASM::Structure input(infile);

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
