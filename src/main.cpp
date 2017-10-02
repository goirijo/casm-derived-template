#include <iostream>
#include <casm/CASM_global_definitions.hh>
#include <casm/crystallography/Structure.hh>
#include <casm/casm_io/VaspIO.hh>


int main()
{
    /**
     * This is where you get to shine. Place all your code in here
     * and use the infrastructure of the repository to compile
     * and install.
     *
     * If you're interested in working with something more complicated
     * than a single main.cpp file is convenient for, check out
     * casm-utilities!
     * https://github.com/goirijo/casm-utilities
     */

    std::cout<<"I am a sad sad executable incapable of anything"<<std::endl;
    std::cout<<"Here is the CASM logo:"<<std::endl;
    CASM::print_splash(std::cout);

    CASM::Structure mypos("POSCAR");

    CASM::VaspIO::PrintPOSCAR myprint(mypos);
    myprint.print(std::cout);

    return 0;
}
