#!/usr/bin/env python
#
# ----------------------------------------------------------------------
#
# Brad T. Aagaard, U.S. Geological Survey
# Charles A. Williams, GNS Science
# Matthew G. Knepley, University of Chicago
#
# This code was developed as part of the Computational Infrastructure
# for Geodynamics (http://geodynamics.org).
#
# Copyright (c) 2010-2015 University of California, Davis
#
# See COPYING for license information.
#
# ----------------------------------------------------------------------
#

## @file tests/2d/quad4/TestCompressRotate.py
##
## @brief Test suite for testing pylith with compression and 90 degree
## CCW rigid body rotation.

import numpy
from TestQuad4 import TestQuad4

from compressrotate_soln import AnalyticalSoln

# Local version of PyLithApp
from pylith.apps.PyLithApp import PyLithApp
class RotateApp(PyLithApp):
  def __init__(self):
    PyLithApp.__init__(self, name="compressrotate")
    return


# Helper function to run PyLith
def run_pylith():
  """
  Run pylith.
  """
  if not "done" in dir(run_pylith):
    # Generate spatial databases
    from compressrotate_gendb import GenerateDB
    db = GenerateDB()
    db.run()

    # Run PyLith
    app = RotateApp()
    app.run()
    run_pylith.done = True
  return


class TestCompressRotate(TestQuad4):
  """
  Test suite for testing pylith with 2-D rigid body rotation.
  """

  def setUp(self):
    """
    Setup for test.
    """
    TestQuad4.setUp(self)
    run_pylith()
    self.outputRoot = "compressrotate"
    self.soln = AnalyticalSoln()
    return


  def calcDisplacements(self, vertices):
    """
    Calculate displacement field given coordinates of vertices.
    """
    return self.soln.displacement(vertices)


  def calcStateVar(self, name, vertices, cells):
    """
    Calculate state variable.
    """
    ncells = self.mesh['ncells']
    pts = numpy.zeros( (ncells, 2), dtype=numpy.float64)
    if name == "total_strain":
      stateVar = self.soln.strain(pts)
    elif name == "stress":
      stateVar = self.soln.stress(pts)
    elif name == "cauchy_stress":
      stateVar = self.soln.cauchy_stress(pts)
    else:
      raise ValueError("Unknown state variable '%s'." % name)

    return stateVar


# ----------------------------------------------------------------------
if __name__ == '__main__':
  import unittest
  from TestCompressRotate import TestCompressRotate as Tester

  suite = unittest.TestSuite()
  suite.addTest(unittest.makeSuite(Tester))
  unittest.TextTestRunner(verbosity=2).run(suite)


# End of file 