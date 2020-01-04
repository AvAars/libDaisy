#pragma once
#ifndef DSY_OSCILLATOR_H
#define DSY_OSCILLATOR_H
#include <stdint.h>
#ifdef __cplusplus
// # Oscillator
// 
//      Synthesis of several waveforms, including polyBLEP bandlimited waveforms.
//
namespace daisysp
{
	class Oscillator
	{
	  public:
		Oscillator() {}
		~Oscillator() {}

// ## Waveforms
//
// Choices for output waveforms, POLYBLEP are appropriately labeled. Others are naive forms.
// ~~~~
		enum
		{
			WAVE_SIN,	
			WAVE_TRI,
			WAVE_SAW,
			WAVE_RAMP,
			WAVE_SQUARE,
			WAVE_POLYBLEP_TRI,
			WAVE_POLYBLEP_SAW,
			WAVE_POLYBLEP_SQUARE,
			WAVE_LAST,
		};
// ~~~~

// ### Init
//
// Initializes the Oscillator 
//
// float sample_rate - sample rate of the audio engine being run, and the frequency that the Process function will be called.
//
// Defaults:
// - freq_ = 100 Hz
// - amp_ = 0.5 
// - waveform_ = sine wave.
//
// ~~~~
		void Init(float sample_rate)
// ~~~~
		{
			sr_		  = sample_rate;
			freq_	  = 100.0f;
			amp_		  = 0.5f;
			phase_	 = 0.0f;
			phase_inc_ = CalcPhaseInc(freq_);
			waveform_  = WAVE_SIN;
		}

// ### SetFreq
//
// Changes the frequency of the Oscillator, and recalculates phase increment.
// ~~~~
		inline void SetFreq(const float f) 
// ~~~~
		{
			freq_	  = f;
			phase_inc_ = CalcPhaseInc(f);
		}

// ### SetAmp
//
// Sets the amplitude of the waveform.
// ~~~~
		inline void SetAmp(const float a) { amp_ = a; }
// ~~~~

// ### SetWaveform
//
// Sets the waveform to be synthesized by the Process() function.
// ~~~~
		inline void SetWaveform(const uint8_t wf) { waveform_ = wf < WAVE_LAST ? wf : WAVE_SIN; }
// ~~~~

// ### Process
//
// Processes the waveform to be generated, returning one sample. This should be called once per sample period.
// ~~~~
		float Process();
// ~~~~

	  private:
		float   CalcPhaseInc(float f);
		uint8_t waveform_;
		float   amp_, freq_;
		float   sr_, phase_, phase_inc_;
		float   last_out_, last_freq_;
	};
} // namespace daisysp
#endif
#endif
