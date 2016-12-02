//-----------------------------------------------------------------------------
// Project     : VST SDK
// Version     : 3.6.0
//
// Category    : Examples
// Filename    : public.sdk/samples/vst/note_expression_synth/source/brownnoise.h
// Created by  : Steinberg, 03/2010
// Description : 
//
//-----------------------------------------------------------------------------
// LICENSE
// (c) 2013, Steinberg Media Technologies GmbH, All Rights Reserved
//-----------------------------------------------------------------------------
// Redistribution and use in source and binary forms, with or without modification,
// are permitted provided that the following conditions are met:
// 
//   * Redistributions of source code must retain the above copyright notice, 
//     this list of conditions and the following disclaimer.
//   * Redistributions in binary form must reproduce the above copyright notice,
//     this list of conditions and the following disclaimer in the documentation 
//     and/or other materials provided with the distribution.
//   * Neither the name of the Steinberg Media Technologies nor the names of its
//     contributors may be used to endorse or promote products derived from this 
//     software without specific prior written permission.
// 
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
// ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED 
// WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. 
// IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, 
// INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, 
// BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, 
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF 
// LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE 
// OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
// OF THE POSSIBILITY OF SUCH DAMAGE.
//-----------------------------------------------------------------------------

#ifndef __brownnoise__
#define __brownnoise__

#include "pluginterfaces/base/ftypes.h"
#include <stdlib.h>
#include <cmath>

namespace Steinberg {
namespace Vst {
namespace NoteExpressionSynth {

//-----------------------------------------------------------------------------
template<class SamplePrecision>
class BrownNoise
{
public:
	BrownNoise (int32 bufferSize, SamplePrecision sampleRate);
	~BrownNoise ();

	SamplePrecision at (int32 pos) const { return buffer[pos]; }
	int32 getSize () const { return bufferSize; }
protected:
	SamplePrecision* buffer;
	int32 bufferSize;
};

//-----------------------------------------------------------------------------
template<class SamplePrecision>
BrownNoise<SamplePrecision>::BrownNoise (int32 bufferSize, SamplePrecision sampleRate)
: buffer (0)
, bufferSize (bufferSize)
{
	buffer = new SamplePrecision [bufferSize];

	const SamplePrecision f = (SamplePrecision)0.0045;
	SamplePrecision accu = (SamplePrecision)0.;
	SamplePrecision y;
	for (int32 frame = 0; frame < bufferSize; frame++)
	{
		y = ((SamplePrecision)rand () / (SamplePrecision)RAND_MAX - (SamplePrecision)0.5) * (SamplePrecision)2.;

		accu = (f * y) + (((SamplePrecision)1.0 - f) * accu);
		y = (SamplePrecision)1.55 * accu * (SamplePrecision)100. / (SamplePrecision)::sqrt (::sqrt (sampleRate));
		buffer[frame] = y;
	}
}

//-----------------------------------------------------------------------------
template<class SamplePrecision>
BrownNoise<SamplePrecision>::~BrownNoise ()
{
	delete [] buffer;
}

}}} // namespaces

#endif
