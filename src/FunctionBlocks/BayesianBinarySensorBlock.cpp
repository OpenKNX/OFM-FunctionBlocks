#include "BayesianBinarySensorBlock.h"
#include "knxprod.h"
#include <cmath>

BayesianBinarySensorBlock::BayesianBinarySensorBlock(uint8_t channelIndex)
    : FunctionBlock(channelIndex, "BAYESIAN")
{
}

uint8_t BayesianBinarySensorBlock::getParamInputEnabled(uint8_t input)
{
    switch (input)
    {
        case 0:
            return ParamFCB_CHLogicKo0D;
        case 1:
            return ParamFCB_CHLogicKo1D;
        case 2:
            return ParamFCB_CHLogicKo2D;
        case 3:
            return ParamFCB_CHLogicKo3D;
        case 4:
            return ParamFCB_CHLogicKo4D;
        case 5:
            return ParamFCB_CHLogicKo5D;
        case 6:
            return ParamFCB_CHLogicKo6D;
        case 7:
            return ParamFCB_CHLogicKo7D;
        case 8:
            return ParamFCB_CHLogicKo8D;
        default:
            openknx.hardware.fatalError(FATAL_SYSTEM, "Invalid input");
            return 0;
    }
}

uint8_t BayesianBinarySensorBlock::getParamProbGivenTrue(uint8_t input)
{
    switch (input)
    {
        case 0:
            return ParamFCB_CHLogicKo0BayesProbTrue;
        case 1:
            return ParamFCB_CHLogicKo1BayesProbTrue;
        case 2:
            return ParamFCB_CHLogicKo2BayesProbTrue;
        case 3:
            return ParamFCB_CHLogicKo3BayesProbTrue;
        case 4:
            return ParamFCB_CHLogicKo4BayesProbTrue;
        case 5:
            return ParamFCB_CHLogicKo5BayesProbTrue;
        case 6:
            return ParamFCB_CHLogicKo6BayesProbTrue;
        case 7:
            return ParamFCB_CHLogicKo7BayesProbTrue;
        case 8:
            return ParamFCB_CHLogicKo8BayesProbTrue;
        default:
            openknx.hardware.fatalError(FATAL_SYSTEM, "Invalid input");
            return 90; // Default: 90%
    }
}

uint8_t BayesianBinarySensorBlock::getParamProbGivenFalse(uint8_t input)
{
    switch (input)
    {
        case 0:
            return ParamFCB_CHLogicKo0BayesProbFalse;
        case 1:
            return ParamFCB_CHLogicKo1BayesProbFalse;
        case 2:
            return ParamFCB_CHLogicKo2BayesProbFalse;
        case 3:
            return ParamFCB_CHLogicKo3BayesProbFalse;
        case 4:
            return ParamFCB_CHLogicKo4BayesProbFalse;
        case 5:
            return ParamFCB_CHLogicKo5BayesProbFalse;
        case 6:
            return ParamFCB_CHLogicKo6BayesProbFalse;
        case 7:
            return ParamFCB_CHLogicKo7BayesProbFalse;
        case 8:
            return ParamFCB_CHLogicKo8BayesProbFalse;
        default:
            openknx.hardware.fatalError(FATAL_SYSTEM, "Invalid input");
            return 10; // Default: 10%
    }
}

void BayesianBinarySensorBlock::readInputKos()
{
    // KOs are automatically assigned (0-8 for inputs)
    // No manual KO configuration needed
}

void BayesianBinarySensorBlock::initMissingInputValues()
{
    for (uint8_t i = 0; i < 9; i++)
    {
        // Check if input is enabled
        if (getParamInputEnabled(i) != 0)
        {
            if (!hasValue(i))
            {
                // Initialize with FALSE if no value received
                auto& ko = getKo(i);
                ko.value(false, DPT_Switch);
            }
        }
    }
}

void BayesianBinarySensorBlock::handleKo(GroupObject &ko)
{
    const int16_t index = FCB_KoCalcIndex(ko.asap());
    if (FCB_KoCHKO0 <= index && index < (ParamFCB_CHBayesianEnableProbOutput ? FCB_KoCHKO8 : FCB_KoCHKO9))
    {
        const uint8_t probability = _calculateBayesianProbability();
        _updateOutputs(probability);
    }    
}

uint8_t BayesianBinarySensorBlock::_calculateBayesianProbability()
{
    // Convert prior from percentage to probability
    const double priorProb = ParamFCB_CHBayesianPrior / 100.0f;
    const double priorNotProb = 1.0f - priorProb;
    
    // Initialize likelihood ratios
    double likelihoodGivenTrue = 1.0f;
    double likelihoodGivenFalse = 1.0f;
    
    // Process each active input directly
    const uint8_t inputCount = 9 - ParamFCB_CHBayesianEnableProbOutput;
    for (uint8_t i = 0; i < inputCount; i++)
    {
        if (getParamInputEnabled(i) != 0 && hasValue(i))
        {
            const float probGivenTrue = getParamProbGivenTrue(i) / 100.0f;
            const float probGivenFalse = getParamProbGivenFalse(i) / 100.0f;

            // observed sensor values
            if (getKo(i).value(DPT_Switch))
            {
                likelihoodGivenTrue *= probGivenTrue;
                likelihoodGivenFalse *= probGivenFalse;
            }
            else
            {
                likelihoodGivenTrue *= (1.0 - probGivenTrue);
                likelihoodGivenFalse *= (1.0 - probGivenFalse);
            }
        }
    }
    
    // Apply Bayes' theorem (works for both active and no inputs)
    const double numerator = likelihoodGivenTrue * priorProb;
    const double denominator = numerator + (likelihoodGivenFalse * priorNotProb);
    
    // Avoid division by zero, fallback to prior
    const double posteriorProb = (denominator == 0.0f) ? priorProb : (numerator / denominator);
    const uint8_t resultPercent = (uint8_t)(posteriorProb * 100.0f);
    return (resultPercent > 100) ? 100 : resultPercent;
}

void BayesianBinarySensorBlock::_updateOutputs(uint8_t probabilityPercent)
{
    // Update probability output if enabled
    if (ParamFCB_CHBayesianEnableProbOutput == 1)
    {
        // <Enumeration Text="Bei jedem Eingangstelegram" Value="0" Id="%ENID%" />
        // <Enumeration Text="Nur bei Änderung des Ausgangswertes" Value="1" Id="%ENID%" />
        if (ParamFCB_CHLogicBehavOut)
            KoFCB_CHKO8.valueCompare(probabilityPercent, DPT_Scaling);
        else
            KoFCB_CHKO8.value(probabilityPercent, DPT_Scaling);
    }

    // Update binary output based on threshold
    bool binaryResult = probabilityPercent >= ParamFCB_CHBayesianThreshold;

    // <Enumeration Text="Bei jedem Eingangstelegram" Value="0" Id="%ENID%" />
    // <Enumeration Text="Nur bei Änderung des Ausgangswertes" Value="1" Id="%ENID%" />
    if (ParamFCB_CHLogicBehavOut)
        KoFCB_CHKO9.valueCompare(binaryResult, DPT_Switch);
    else
        KoFCB_CHKO9.value(binaryResult, DPT_Switch);
}

