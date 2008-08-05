/******************************************************************************
*       SOFA, Simulation Open-Framework Architecture, version 1.0 beta 3      *
*                (c) 2006-2008 MGH, INRIA, USTL, UJF, CNRS                    *
*                                                                             *
* This library is free software; you can redistribute it and/or modify it     *
* under the terms of the GNU Lesser General Public License as published by    *
* the Free Software Foundation; either version 2.1 of the License, or (at     *
* your option) any later version.                                             *
*                                                                             *
* This library is distributed in the hope that it will be useful, but WITHOUT *
* ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or       *
* FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License *
* for more details.                                                           *
*                                                                             *
* You should have received a copy of the GNU Lesser General Public License    *
* along with this library; if not, write to the Free Software Foundation,     *
* Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301 USA.          *
*******************************************************************************
*                              SOFA :: Framework                              *
*                                                                             *
* Authors: M. Adam, J. Allard, B. Andre, P-J. Bensoussan, S. Cotin, C. Duriez,*
* H. Delingette, F. Falipou, F. Faure, S. Fonteneau, L. Heigeas, C. Mendoza,  *
* M. Nesme, P. Neumann, J-P. de la Plata Alcade, F. Poyer and F. Roy          *
*                                                                             *
* Contact information: contact@sofa-framework.org                             *
******************************************************************************/
#ifndef SOFA_CORE_COMPONENTMODEL_BEHAVIOR_MECHANICALSTATE_H
#define SOFA_CORE_COMPONENTMODEL_BEHAVIOR_MECHANICALSTATE_H

#include <sofa/core/componentmodel/behavior/BaseMechanicalState.h>
#include <sofa/core/componentmodel/behavior/State.h>

namespace sofa
{

namespace core
{

namespace componentmodel
{

namespace behavior
{

/**
 *  \brief Component storing all state vectors of a simulated body (position,
 *  velocity, etc), using the datatype specified in the templace.
 *
 *  The given DataTypes class should define the following internal types:
 *  \li \code Real \endcode : scalar values (float or double).
 *  \li \code Coord \endcode : position values.
 *  \li \code Deriv \endcode : derivative values (velocity, forces, displacements).
 *  \li \code VecReal \endcode : container of scalar values with the same API as sofa::helper::vector.
 *  \li \code VecCoord \endcode : container of Coord values with the same API as sofa::helper::vector.
 *  \li \code VecDeriv \endcode : container of Deriv values with the same API as sofa::helper::vector.
 *  \li \code SparseDeriv \endcode : index + Deriv value (entry of a sparse vector).
 *  \li \code SparseVecDeriv \endcode : sparse vector of Deriv values (defining coefficient of a constraint).
 *  \li \code VecConst \endcode : vector of constraints (i.e. of SparseVecDeriv).
 *
 *  Other vectors can be allocated to store other temporary values.
 *  Vectors can be assigned efficiently by just swapping pointers.
 *
 *  In addition to state vectors, the current constraint system matrix is also
 *  stored, containing the coefficient of each constraint defined over the DOFs
 *  in this body.
 *
 */
template<class TDataTypes>
class MechanicalState : public BaseMechanicalState, public State<TDataTypes>
{
public:
    typedef TDataTypes DataTypes;
    /// Scalar values (float or double).
    typedef typename DataTypes::Real Real;
    /// Position values.
    typedef typename DataTypes::Coord Coord;
    /// Derivative values (velocity, forces, displacements).
    typedef typename DataTypes::Deriv Deriv;
    /// Container of scalar values with the same API as sofa::helper::vector.
    typedef typename DataTypes::VecReal VecReal;
    /// Container of Coord values with the same API as sofa::helper::vector.
    typedef typename DataTypes::VecCoord VecCoord;
    /// Container of Deriv values with the same API as sofa::helper::vector.
    typedef typename DataTypes::VecDeriv VecDeriv;
    /// Index + Deriv value (entry of a sparse vector).
    typedef typename DataTypes::SparseDeriv SparseDeriv;
    /// Sparse vector of Deriv values (defining coefficient of a constraint).
    typedef typename DataTypes::SparseVecDeriv SparseVecDeriv;
    /// Vector of constraints (i.e. of SparseVecDeriv).
    typedef typename DataTypes::VecConst VecConst;

    virtual ~MechanicalState() { }

    /// Return the free-motion velocity vector (read-write access).
    virtual VecDeriv* getVfree() = 0;
    /// Return the current velocity vector (read-write access).
    virtual VecDeriv* getV() = 0;
    /// Return the force vector (read-write access).
    virtual VecDeriv* getF() = 0;
    /// Return the external forces vector (read-write access).
    virtual VecDeriv* getExternalForces() = 0;
    /// Return the displacement vector (read-write access).
    virtual VecDeriv* getDx() = 0;
    /// Return the constraints system matrix (read-write access).
    virtual VecConst* getC() = 0;
    /// Return the free-motion position vector (read-write access).
    virtual VecCoord* getXfree() = 0;
    /// Return the current position vector (read-write access).
    virtual VecCoord* getX() = 0;
    /// Return the current position vector (read-write access).
    virtual VecCoord* getX0() = 0;

    /// Return the current position vector (read-only access).
    virtual const VecCoord* getX()  const = 0;
    /// Return the current velocity vector (read-only access).
    virtual const VecDeriv* getV()  const = 0;
    /// Return the force vector (read-only access).
    virtual const VecDeriv* getF()  const = 0;
    /// Return the external forces vector (read-write access).
    virtual const VecDeriv* getExternalForces() const = 0;
    /// Return the displacement vector (read-only access).
    virtual const VecDeriv* getDx() const = 0;
    /// Return the constraints system matrix (read-only access).
    virtual const VecConst* getC() const = 0;
    /// Return the free-motion position vector (read-only access).
    virtual const VecCoord* getXfree()  const = 0;
    /// Return the free-motion velocity vector (read-only access).
    virtual const VecDeriv* getVfree() const = 0;
    /// Return the current position vector (read-only access).
    virtual const VecCoord* getX0()  const = 0;
    /// Return the initial velocity vector (read-only access).
    virtual const VecDeriv* getV0()  const = 0;

    /// Return a VecCoord given its index
    virtual VecCoord* getVecCoord(unsigned int index) = 0;

    /// Return a VecCoord given its index, or NULL if it does not exists
    virtual const VecCoord* getVecCoord(unsigned int index) const = 0;

    /// Return a VecDeriv given its index
    virtual VecDeriv* getVecDeriv(unsigned int index) = 0;

    /// Return a VecDeriv given its index, or NULL if it does not exists
    virtual const VecDeriv* getVecDeriv(unsigned int index) const = 0;

    /// Return a VecConst given its index
    virtual VecConst* getVecConst(unsigned int index) = 0;

    /// Return a VecConst given its index, or NULL if it does not exists
    virtual const VecConst* getVecConst(unsigned int index) const = 0;


    /// Get the indices of the particles located in the given bounding box
    virtual void getIndicesInSpace(sofa::helper::vector<unsigned>& /*indices*/, Real /*xmin*/, Real /*xmax*/,Real /*ymin*/, Real /*ymax*/, Real /*zmin*/, Real /*zmax*/) const=0;

    /// Add a constraint ID
    virtual void setConstraintId(unsigned int ) = 0;
    /// Return the constraint IDs corresponding to the entries in the constraints matrix returned by getC()
    virtual sofa::helper::vector<unsigned int>& getConstraintId() = 0;


    virtual std::string getTemplateName() const
    {
        return templateName(this);
    }

    static std::string templateName(const MechanicalState<DataTypes>* = NULL)
    {
        return DataTypes::Name();
    }

    static std::string Name(const State<DataTypes>* = NULL)
    {
        return std::string("MechanicalState");
    }

};

} // namespace behavior

} // namespace componentmodel

} // namespace core

} // namespace sofa

#endif
