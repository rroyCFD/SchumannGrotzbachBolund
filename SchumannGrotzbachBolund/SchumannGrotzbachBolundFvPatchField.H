/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | Copyright (C) 1991-2009 OpenCFD Ltd.
     \\/     M anipulation  |
-------------------------------------------------------------------------------
License
    This file is part of OpenFOAM.

    OpenFOAM is free software; you can redistribute it and/or modify it
    under the terms of the GNU General Public License as published by the
    Free Software Foundation; either version 2 of the License, or (at your
    option) any later version.

    OpenFOAM is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
    for more details.

    You should have received a copy of the GNU General Public License
    along with OpenFOAM; if not, write to the Free Software Foundation,
    Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA

Class
    Foam::incompressible::LESModels::SchumannGrotzbachBolundFvPatchField

Description
    Wall boundary condition for total shear stress at a solid boundary.  
    Stresses are computed using the Schumann/Grotzbach formulation.  Can be
    used in either horizontal-average or local mode.

SourceFiles
    SchumannGrotzbachBolundFvPatchField.C

\*---------------------------------------------------------------------------*/

#ifndef SchumannGrotzbachBolundFvPatchField_H
#define SchumannGrotzbachBolundFvPatchField_H

#include "fixedValueFvPatchFields.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

/*---------------------------------------------------------------------------*\
     Class SchumannGrotzbachBolundFvPatchField Declaration
\*---------------------------------------------------------------------------*/

class SchumannGrotzbachBolundFvPatchField
:
    public fixedValueFvPatchSymmTensorField
{

private:

    // Private data

        // -Type of application of Monin-Obuhkov scaling, local or nonlocal
        word averageType_;

        //- Von Karman constant
        scalar kappa_;

        //- Constant for unstable Monin-Obuhkov scaling law
        scalar betaM_;

        // -Constant for stable Monin-Obuhkov scaling law
        scalar gammaM_;

        //- Sea roughness height
        scalar z0Sea_;

        //- Terrain roughness height
        scalar z0Terrain_;

        // reference height of the terrain
        scalar refHeight_;

        //- Roughness height
        scalarField z0_;

    // Private member functions
       
        // -Function to transform vectors from Cartesian into terrain-local
        //  coordinates
        vector transformVectorCartToLocal
        (
             vector v,
             vector xP,
             vector yP,
             vector zP
        );

        // -Function to transform symmetric tensors from terrain-local to
        //  Cartesian coordinates
        symmTensor transformSymmTensorLocalToCart
        (
             symmTensor SP,
             vector xP,
             vector yP,
             vector zP
        );

        // -Function to calculate friction velocity using Monin-Obuhkov
        //  similarity laws
        void uStarEvaluate
        (
             scalar &uStar,
             scalar& L,
             scalar& phiM,
             scalar U,
             scalar z1,
             scalar z0,
             scalar kappa,
             scalar gammaM,
             scalar betaM,
             scalar g,
             scalar TRef,
             scalar qw,
             scalar eps,
             scalar tol,
             label iter,
             label iterMax
        );  

        void getRoughnessHeight(scalarField& z0_);
public:

    //- Runtime type information
    TypeName("SchumannGrotzbachBolund");


    // Constructors

        //- Construct from patch and internal field
        SchumannGrotzbachBolundFvPatchField
        (
            const fvPatch&,
            const DimensionedField<symmTensor, volMesh>&
        );

        //- Construct from patch, internal field and dictionary
        SchumannGrotzbachBolundFvPatchField
        (
            const fvPatch&,
            const DimensionedField<symmTensor, volMesh>&,
            const dictionary&
        );

        //- Construct by mapping given
        //  stressABLWallFunctionFvPatchScalarField
        //  onto a new patch
        SchumannGrotzbachBolundFvPatchField
        (
            const SchumannGrotzbachBolundFvPatchField&,
            const fvPatch&,
            const DimensionedField<symmTensor, volMesh>&,
            const fvPatchFieldMapper&
        );

        //- Construct as copy
        SchumannGrotzbachBolundFvPatchField
        (
            const SchumannGrotzbachBolundFvPatchField&
        );

        //- Construct and return a clone
        virtual tmp<fvPatchSymmTensorField> clone() const
        {
            return tmp<fvPatchSymmTensorField>
            (
                new SchumannGrotzbachBolundFvPatchField(*this)
            );
        }

        //- Construct as copy setting internal field reference
        SchumannGrotzbachBolundFvPatchField
        (
            const SchumannGrotzbachBolundFvPatchField&,
            const DimensionedField<symmTensor, volMesh>&
        );

        //- Construct and return a clone setting internal field reference
        virtual tmp<fvPatchSymmTensorField> clone
        (
            const DimensionedField<symmTensor, volMesh>& iF
        ) const
        {
            return tmp<fvPatchSymmTensorField>
            (
                new SchumannGrotzbachBolundFvPatchField
                (
                    *this,
                    iF
                )
            );
        }


    // Member functions

        // Access functions
            //- Return z_0
            scalarField& z0()
            {
                return z0_;
            }

            //- Return reference height for terrain
            const scalar& refHeight()
            {
                return refHeight_;
            }

        // Evaluation functions

            //- Evaluate the patchField
            virtual void evaluate(const Pstream::commsTypes);


        // I-O

            //- Write
            void write(Ostream&) const;
};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
