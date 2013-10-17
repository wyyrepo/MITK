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

#ifndef MITKUSTelemedBModeControls_H_HEADER_INCLUDED_
#define MITKUSTelemedBModeControls_H_HEADER_INCLUDED_

#include "mitkUSTelemedSDKHeader.h"
#include "mitkUSControlInterfaceBMode.h"

#include <itkObjectFactory.h>

namespace mitk {
  /**
    * \brief Implementation of mitk::USControlInterfaceBMode for Telemed ultrasound devices.
    * See documentation of mitk::USControlInterfaceBMode for a description of the interface methods.
    */
  class USTelemedBModeControls : public USControlInterfaceBMode
  {
  public:
    mitkClassMacro(USTelemedBModeControls, USControlInterfaceBMode);
    itkNewMacro(Self);

    /**
      * Scan mode is set to b mode when this controls are activated.
      * All necessary controls are created at the Telemed API.
      */
    virtual void SetIsActive( bool );

    /**
      * \return true if API controls are created and scan mode is set to b mode
      */
    virtual bool GetIsActive( );

    virtual double GetScanningFrequency( );
    virtual void SetScanningFrequency( double frequency );
    virtual std::vector<double> GetScanningFrequencyValues( );

    virtual double GetScanningPower( );
    virtual void SetScanningPower( double power );
    virtual double GetScanningPowerMin( );
    virtual double GetScanningPowerMax( );
    virtual double GetScanningPowerTick( );

    virtual double GetScanningDepth( );
    virtual void SetScanningDepth( double );
    virtual std::vector<double> GetScanningDepthValues( );

    virtual double GetScanningGain( );
    virtual void SetScanningGain( double );
    virtual double GetScanningGainMin( );
    virtual double GetScanningGainMax( );
    virtual double GetScanningGainTick( );

    virtual double GetScanningRejection( );
    virtual void SetScanningRejection( double );
    virtual double GetScanningRejectionMin( );
    virtual double GetScanningRejectionMax( );
    virtual double GetScanningRejectionTick( );

    /**
      * \brief Setter for the IUsgDataView necesary for communicating with the Telemed API.
      * This method is just for internal use of the mitk::USTelemedDevice.
      */
    void SetUsgDataView( Usgfw2Lib::IUsgDataView* );

    void ReinitializeControls( );

  protected:
    USTelemedBModeControls();
    virtual ~USTelemedBModeControls();

    void CreateControls( );
    void ReleaseControls( );

    double GetScanningFrequencyAPI( );

    Usgfw2Lib::IUsgDataView*             m_UsgDataView;      // main SDK object for comminucating with the Telemed API
    Usgfw2Lib::IUsgPower*                m_PowerControl;     // control for scanning power
    Usgfw2Lib::IUsgProbeFrequency2*      m_FrequencyControl; // control for scanning frequency
    Usgfw2Lib::IUsgDepth*                m_DepthControl;     // control for B mode scanning depth
    Usgfw2Lib::IUsgGain*                 m_GainControl;      // control for B mode scanning gain
    Usgfw2Lib::IUsgRejection2*           m_RejectionControl; // control for B mode scanning rejection

    bool                      m_Active;

    double*                   m_PowerSteps;       // array holding possible power values: [min, max, tick]
    double*                   m_GainSteps;        // array holding possible gains: [min, max, tick]
    double*                   m_RejectionSteps;   // array holding possible rejections: [min, max, tick]
  };
} // namespace mitk

#endif // MITKUSTelemedBModeControls_H_HEADER_INCLUDED_