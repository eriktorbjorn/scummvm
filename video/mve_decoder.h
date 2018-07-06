/* ScummVM - Graphic Adventure Engine
 *
 * ScummVM is the legal property of its developers, whose names
 * are too numerous to list here. Please refer to the COPYRIGHT
 * file distributed with this source distribution.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 */

#ifndef VIDEO_MVE_DECODER
#define VIDEO_MVE_DECODER

#include "graphics/surface.h"
#include "video/video_decoder.h"

namespace Common {
class SeekableReadStream;
}

namespace Video {

/**
 * Decoder for Interplay MVE videos.
 *
 * Video decoder used in engines:
 *  - None. Yet.
 */
class MVEDecoder : public VideoDecoder {
public:
	MVEDecoder();
	~MVEDecoder();
	void close();
	bool loadStream(Common::SeekableReadStream *stream);

protected:
	void readNextPacket();

private:
	void parseChunk(Common::SeekableReadStream *chunk);

	class MVETrack {
	public:
		MVETrack() {
			_endOfTrack = false;
		}

		void setEndOfTrack() {
			_endOfTrack = true;
		}
	protected:
		bool _endOfTrack;
	};

	class MVEAudioTrack : public MVETrack, public AudioTrack {
	public:
		MVEAudioTrack(Audio::Mixer::SoundType soundType);
	};

	class MVEVideoTrack : public MVETrack, public FixedRateVideoTrack {
	public:
		MVEVideoTrack(uint16 width, uint16 height, Common::Rational frameRate);
		~MVEVideoTrack();

		uint16 getWidth() const { return _surface->w; }
		uint16 getHeight() const { return _surface->h; }
		Graphics::PixelFormat getPixelFormat() const { return _surface->format; }
		Graphics::Surface *decodeNextFrame() { return _surface; }

		int getCurFrame() const { return _curFrame; }
		Common::Rational getFrameRate() const { return _frameRate; }

	private:
		Graphics::Surface *_surface;
		byte _palette[3 * 256];
		int _curFrame;
		Common::Rational _frameRate;
	};

	Common::SeekableReadStream *_stream;
	MVEAudioTrack *_audioTrack;
	MVEVideoTrack *_videoTrack;

	uint16 _videoWidth;
	uint16 _videoHeight;
};

} // End of namespace Video

#endif
