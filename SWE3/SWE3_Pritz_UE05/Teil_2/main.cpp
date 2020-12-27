#include "part.h"
#include "formatter.h"
using PartsLists::Part;
using PartsLists::CompositePart;

void test_reference(formatting::SetFormatter const& setf, formatting::HierarchyFormatter hierf)
{
	Part beink("Bein (klein)");
	Part sitzf("Sitzflaeche");

	CompositePart sessel("Sessel");
	sessel.addPart(&beink);
	sessel.addPart(&beink);
	sessel.addPart(&beink);
	sessel.addPart(&beink);
	sessel.addPart(&sitzf);

	Part being("Bein (gross)");
	Part tischf("Tischflaeche");

	CompositePart tisch("Tisch");
	tisch.addPart(&being);
	tisch.addPart(&being);
	tisch.addPart(&being);
	tisch.addPart(&being);
	tisch.addPart(&tischf);

	CompositePart sitzgarnitur("Sitzgarnitur");
	sitzgarnitur.addPart(&sessel);
	sitzgarnitur.addPart(&sessel);
	sitzgarnitur.addPart(&tisch);

	setf.printParts(&sitzgarnitur);
	hierf.printParts(&sitzgarnitur);
}

void test_alter(formatting::SetFormatter const& setf, formatting::HierarchyFormatter hierf)
{
	Part beink("Bein (klein)");
	Part sitzf("Sitzflaeche");

	CompositePart sessel("Sessel");
	sessel.addPart(&beink);
	sessel.addPart(&beink);
	sessel.addPart(&beink);
	sessel.addPart(&beink);
	sessel.addPart(&sitzf);

	Part being("Bein (gross)");
	Part tischf("Tischflaeche");

	CompositePart tisch("Tisch");
	tisch.addPart(&being);
	tisch.addPart(&being);
	tisch.addPart(&being);
	tisch.addPart(&being);
	tisch.addPart(&tischf);

	CompositePart sitzgarnitur("Sitzgarnitur");
	sitzgarnitur.addPart(&sessel);
	sitzgarnitur.addPart(&sessel);
	sitzgarnitur.addPart(&tisch);

	Part polster("Polster");
	CompositePart polsterSessel("Sessel");
	polsterSessel.addPart(&beink);
	polsterSessel.addPart(&beink);
	polsterSessel.addPart(&beink);
	polsterSessel.addPart(&beink);
	polsterSessel.addPart(&sitzf);
	polsterSessel.addPart(&polster);

	sitzgarnitur.getParts()[0] = &polsterSessel;
	CompositePart* sub = dynamic_cast<CompositePart*>(sitzgarnitur.getParts()[0]);
	sub->getParts()[0] = &tisch;

	setf.printParts(&sitzgarnitur);
	hierf.printParts(&sitzgarnitur);
}

void test_empty(formatting::SetFormatter const& setf, formatting::HierarchyFormatter hierf)
{
	CompositePart test("null_part");
	test.addPart(nullptr);

	setf.printParts(&test);
	hierf.printParts(&test);
}

void test_equals(formatting::HierarchyFormatter hierf)
{
	Part p1("Sessel");
	Part p2("Sessel");
	Part p3("Polster");
	if(p1.equals(&p2))
	{
		std::cout << "Parts are equal.\n";
	}
	else
	{
		std::cout << "Parts are unequal.\n";
	}
	std::cout << "Comparison:\n";
	hierf.printParts(&p1);
	hierf.printParts(&p2);

	CompositePart sesselpolster1("Sesselpolster");
	sesselpolster1.addPart(&p2);
	sesselpolster1.addPart(&p3);

	Part p4("Stuhl");
	CompositePart sesselpolster2("Sesselpolster");
	sesselpolster2.addPart(&p4);
	sesselpolster2.addPart(&p3);

	if(sesselpolster1.equals(&sesselpolster2))
	{
		std::cout << "Compositeparts are equal.\n";
	}
	else
	{
		std::cout << "Compositeparts are unequal.\n";
	}
	std::cout << "Comparison:\n";
	hierf.printParts(&sesselpolster1);
	hierf.printParts(&sesselpolster2);

	std::cout << "Swapping 'Stuhl' for 'Sessel':\n";
	sesselpolster2.getParts()[0] = &p2;

	hierf.printParts(&sesselpolster1);
	hierf.printParts(&sesselpolster2);

	if (sesselpolster1.equals(&sesselpolster2))
	{
		std::cout << "Now they are equal!\n";
	}
}

void test_store(formatting::HierarchyFormatter hierf)
{
	Part beink("Bein (klein)");
	Part sitzf("Sitzflaeche");

	CompositePart sessel("Sessel");
	sessel.addPart(&beink);
	sessel.addPart(&beink);
	sessel.addPart(&beink);
	sessel.addPart(&beink);
	sessel.addPart(&sitzf);

	Part being("Bein (gross)");
	Part tischf("Tischflaeche");

	CompositePart tisch("Tisch");
	tisch.addPart(&being);
	tisch.addPart(&being);
	tisch.addPart(&being);
	tisch.addPart(&being);
	tisch.addPart(&tischf);

	CompositePart sitzgarnitur("Sitzgarnitur");
	sitzgarnitur.addPart(&sessel);
	sitzgarnitur.addPart(&sessel);
	sitzgarnitur.addPart(&tisch);

	sitzgarnitur.store("sitzgarnitur.csv");

	hierf.printParts(&sitzgarnitur);
}

void test_load(formatting::HierarchyFormatter hierf)
{
	CompositePart copy("Platzhalter");
	copy.load("sitzgarnitur.csv");

	hierf.printParts(&copy);
}

void main()
{
	formatting::SetFormatter setf;
	formatting::HierarchyFormatter hierf;

	//test_reference(setf, hierf);
	//test_alter(setf, hierf);
	//test_empty(setf, hierf);
	//test_equals(hierf);
	//test_store(hierf);
	test_load(hierf);
}