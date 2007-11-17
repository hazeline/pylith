// -*- C++ -*-
//
// ======================================================================
//
//                           Brad T. Aagaard
//                        U.S. Geological Survey
//
// {LicenseText}
//
// ======================================================================
//

/**
 * @file pylith/feassemble/IntegratorElasticity.hh
 *
 * @brief Object containing general elasticity operations for implicit
 * and explicit time integration of the elasticity equation.
 */

#if !defined(pylith_feassemble_integratorelasticity_hh)
#define pylith_feassemble_integratorelasticity_hh

#include "Integrator.hh" // ISA Integrator
#include "pylith/utils/array.hh" // USES std::vector, double_array

namespace pylith {
  namespace feassemble {
    class IntegratorElasticity;
    class TestIntegratorElasticity;
  } // feassemble

  namespace materials {
    class ElasticMaterial;
  } // feassemble
} // pylith

class pylith::feassemble::IntegratorElasticity : public Integrator
{ // IntegratorElasticity
  friend class TestIntegratorElasticity; // unit testing

// PUBLIC TYPEDEFS //////////////////////////////////////////////////////
public :

  typedef void (*totalStrain_fn_type)(std::vector<double_array>*,
				      const double_array&,
				      const double_array&,
				      const int);
  

// PUBLIC MEMBERS ///////////////////////////////////////////////////////
public :

  /// Constructor
  IntegratorElasticity(void);

  /// Destructor
  ~IntegratorElasticity(void);

  /** Set material.
   *
   * @param m Elastic material.
   */
  void material(materials::ElasticMaterial* m);

  /** Determine whether we need to recompute the Jacobian.
   *
   * @returns True if Jacobian needs to be recomputed, false otherwise.
   */
  bool needNewJacobian(void);

  /** Update state variables as needed.
   *
   * @param t Current time
   * @param field Current solution field.
   * @param mesh Finite-element mesh
   */
  void updateState(const double t,
		   const ALE::Obj<real_section_type>& field,
		   const ALE::Obj<Mesh>& mesh);

  /** Verify configuration is acceptable.
   *
   * @param mesh Finite-element mesh
   */
  void verifyConfiguration(const ALE::Obj<Mesh>& mesh);

// PROTECTED METHODS ////////////////////////////////////////////////////
protected :

  /** Integrate elasticity term in residual for 1-D cells.
   *
   * @param stress Stress tensor for cell at quadrature points.
   */
  void _elasticityResidual1D(const std::vector<double_array>& stress);

  /** Integrate elasticity term in residual for 2-D cells.
   *
   * @param stress Stress tensor for cell at quadrature points.
   */
  void _elasticityResidual2D(const std::vector<double_array>& stress);

  /** Integrate elasticity term in residual for 3-D cells.
   *
   * @param stress Stress tensor for cell at quadrature points.
   */
  void _elasticityResidual3D(const std::vector<double_array>& stress);

  /** Integrate elasticity term in Jacobian for 1-D cells.
   *
   * @param elasticConsts Matrix of elasticity constants at quadrature points.
   */
  void _elasticityJacobian1D(const std::vector<double_array>& elasticConsts);

  /** Integrate elasticity term in Jacobian for 2-D cells.
   *
   * @param elasticConsts Matrix of elasticity constants at quadrature points.
   */
  void _elasticityJacobian2D(const std::vector<double_array>& elasticConsts);

  /** Integrate elasticity term in Jacobian for 3-D cells.
   *
   * @param elasticConsts Matrix of elasticity constants at quadrature points.
   */
  void _elasticityJacobian3D(const std::vector<double_array>& elasticConsts);

  /** Compute total strain in at quadrature points of a cell.
   *
   * @param strain Strain tensor at quadrature points.
   * @param basisDeriv Derivatives of basis functions at quadrature points.
   * @param disp Displacement at vertices of cell.
   * @param dimension Dimension of cell.
   * @param numBasis Number of basis functions for cell.
   */

  static
  void _calcTotalStrain1D(std::vector<double_array>* strain,
			  const double_array& basisDeriv,
			  const double_array& disp,
			  const int numBasis);

  /** Compute total strain in at quadrature points of a cell.
   *
   * @param strain Strain tensor at quadrature points.
   * @param basisDeriv Derivatives of basis functions at quadrature points.
   * @param disp Displacement at vertices of cell.
   * @param numBasis Number of basis functions for cell.
   */

  static
  void _calcTotalStrain2D(std::vector<double_array>* strain,
			  const double_array& basisDeriv,
			  const double_array& disp,
			  const int numBasis);

  /** Compute total strain in at quadrature points of a cell.
   *
   * @param strain Strain tensor at quadrature points.
   * @param basisDeriv Derivatives of basis functions at quadrature points.
   * @param disp Displacement at vertices of cell.
   * @param numBasis Number of basis functions for cell.
   */

  static
  void _calcTotalStrain3D(std::vector<double_array>* strain,
			  const double_array& basisDeriv,
			  const double_array& disp,
			  const int numBasis);

// NOT IMPLEMENTED //////////////////////////////////////////////////////
private :

  /// Not implemented.
  IntegratorElasticity(const IntegratorElasticity& i);

  /// Not implemented
  const IntegratorElasticity& operator=(const IntegratorElasticity&);

// PROTECTED MEMBERS ////////////////////////////////////////////////////
protected :

  /// Elastic material associated with integrator
  materials::ElasticMaterial* _material;

  // Optimization
  std::map<int, int> _dispTags; ///< Tags indexing displacement field.
  std::map<int, int> _residualTags; ///< Tags indexing residual field.

}; // IntegratorElasticity

#endif // pylith_feassemble_integratorelasticity_hh


// End of file 
