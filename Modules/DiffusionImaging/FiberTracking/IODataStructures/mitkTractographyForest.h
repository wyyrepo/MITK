/*===================================================================

The Medical Imaging Interaction Toolkit (MITK)

Copyright (c) German Cancer Research Center,
Division of Medical and Biological Informatics.
All rights reserved.

This software is distributed WITHOUT ANY WARRANTY; without
even the implied warranty of MERCHANTABILITY or FITNESS FOR
A PARTICULAR PURPOSE.

See LICENSE.txt or http://www.mitk.org for details.

===================================================================*/


#ifndef _MITK_TractographyForest_H
#define _MITK_TractographyForest_H

#include <mitkBaseData.h>
#include <MitkFiberTrackingExports.h>

#undef DIFFERENCE
#define VIGRA_STATIC_LIB
#include <vigra/random_forest.hxx>

namespace mitk {

/**
   * \brief Class containing random forest datastructures used for fiber tractography;   */
class MITKFIBERTRACKING_EXPORT TractographyForest : public BaseData
{
public:

    virtual void UpdateOutputInformation() override;
    virtual void SetRequestedRegionToLargestPossibleRegion() override;
    virtual bool RequestedRegionIsOutsideOfTheBufferedRegion() override;
    virtual bool VerifyRequestedRegion() override;
    virtual void SetRequestedRegion(const itk::DataObject*) override;

    mitkClassMacro( TractographyForest, BaseData )
    itkFactorylessNewMacro(Self)
    itkCloneMacro(Self)
    mitkNewMacro1Param(Self, std::shared_ptr< vigra::RandomForest<int> >) // custom constructor

    int GetNumFeatures();
    int GetNumTrees();
    int GetNumClasses();
    int GetMaxTreeDepth();
    int IndexToClassLabel(int idx);
    bool HasForest();

protected:

    TractographyForest( std::shared_ptr< vigra::RandomForest<int> > forest = nullptr );
    virtual ~TractographyForest();

private:

    std::shared_ptr< vigra::RandomForest<int> > m_Forest;   ///< random forest classifier

};

} // namespace mitk

#endif /*  _MITK_TractographyForest_H */
