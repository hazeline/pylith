// -*- C++ -*-
//
// ----------------------------------------------------------------------
//
// Brad T. Aagaard, U.S. Geological Survey
// Charles A. Williams, GNS Science
// Matthew G. Knepley, University of Chicago
//
// This code was developed as part of the Computational Infrastructure
// for Geodynamics (http://geodynamics.org).
//
// Copyright (c) 2010-2012 University of California, Davis
//
// See COPYING for license information.
//
// ----------------------------------------------------------------------
//

#include <portinfo>

#include "TestDirichletBCLine2b.hh" // Implementation of class methods

#include "data/DirichletDataLine2b.hh" // USES DirichletDataLine2b

// ----------------------------------------------------------------------
CPPUNIT_TEST_SUITE_REGISTRATION( pylith::bc::TestDirichletBCLine2b );

// ----------------------------------------------------------------------
// Setup testing data.
void
pylith::bc::TestDirichletBCLine2b::setUp(void)
{ // setUp
  _data = new DirichletDataLine2b();
} // setUp


// End of file 