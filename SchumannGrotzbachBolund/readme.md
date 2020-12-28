## Application : SchumannGrotzbachBolund (Wall shear-stress boundary condition for inhomogeneous surface)

### Author:
- Rajib Roy
- University of Wyoming
- rroy@uwyo.edu, roy.rajib@live.com

### Description:

Wall boundary condition for total shear stress at a solid (impermiable) boundary. Stresses are computed using the Schumann/Grotzbach formulation. In an inhomogeneous surface, average velocity is obtained though a time average instead of a horizontal-average or local mode.

The Boundary Condition (BC) is developed based on the [SchumannGrotzbach](https://github.com/NREL/SOWFA/tree/master/src/finiteVolume/fields/fvPatchFields/derived/surfaceStressModels/SchumannGrotzbach) BC implemented in the [SOWFA](https://github.com/NREL/SOWFA) toolbox for OpenFoam developed at [NREL](https://nwtc.nrel.gov/SOWFA).

**Usage:**
```
an_inhomogeneous_boundary
    {
        type            SchumannGrotzbachBolund;
        // default parameter values
        kappa           0.4; 
        z0              uniform 0.0006; // surface roughness length
        z0Sea           0.015;
        z0Terrain       0.0006;
        refHeight       0.75;
        betaM           16;
        gammaM          5;
        averageType     "local"; "plannerAverage"
        value           uniform (0 0 0 0 0 0); // place-holder for the stress tensor
    }
```

### Disclaiimer:

This application is built based on [OpenFOAM version-6](https://openfoam.org/release/6/). Please read the _About OpenFOAM_ section to learn more on OpenFOAM.

The application is free to use. The author neither provide any warranty nor shall be liable for any damage incurred from this application.



#### About OpenFOAM

OpenFOAM is the leading free, open source software for computational fluid dynamics (CFD), owned by the OpenFOAM Foundation and distributed exclusively under the [General Public Licence (GPL)](http://www.gnu.org/copyleft/gpl.html). The GPL gives users the freedom to modify and redistribute the software and a guarantee of continued free use, within the terms of the licence. To learn more visit [https://openfoam.org/](https://openfoam.org/)
