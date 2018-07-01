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

#include "common/debug.h"
#include "common/stream.h"
#include "video/mve_decoder.h"

namespace Video {

enum {
	kChunkInitializeAudio			= 0,
	kChunkAudio				= 1,
	kChunkInitializeVideo			= 2,
	kChunkVideo				= 3,
	kChunkShutdown				= 4,
	kChunkEnd				= 5
};

enum {
	kOpcodeEndOfStream			= 0,
	kOpcodeEndOfChunk			= 1,
	kOpcodeCreateTimer			= 2,
	kOpcodeInitializeAudioBuffers		= 3,
	kOpcodeStartStopAudio			= 4,
	kOpcodeInitializeVideoBuffers		= 5,
	kOpcodeUnknown6				= 6,
	kOpcodeSendBufferToDisplay		= 7,
	kOpcodeAudioFrameData			= 8,
	kOpcodeAudioFrameSilence		= 9,
	kOpcodeInitializeVideoMode		= 10,
	kOpcodeCreateGradient			= 11,
	kOpcodeSetPalette			= 12,
	kOpcodeSetPaletteEntriesCompressed	= 13,
	kOpcodeUnknown14			= 14,
	kOpcodeSetDecodingMap			= 15,
	kOpcodeUnknown16			= 16,
	kOpcodeVideoData			= 17,
	kOpcodeUnknown18			= 18,
	kOpcodeUnknown19			= 19,
	kOpcodeUnknown20			= 20,
	kOpcodeUnknown21			= 21
};

MVEDecoder::MVEDecoder() {
	_stream = 0;
	_videoTrack = 0;
	_audioTrack = 0;
}

MVEDecoder::~MVEDecoder() {
	close();
}

void MVEDecoder::close() {
	VideoDecoder::close();

	_audioTrack = 0;
	_videoTrack = 0;

	_videoWidth = 0;
	_videoHeight = 0;
}

bool MVEDecoder::loadStream(Common::SeekableReadStream *stream) {
	close();

	_stream = stream;

	byte buffer[20];
	_stream->read(buffer, sizeof(buffer));
	if (memcmp(buffer, "Interplay MVE File\x1A\x00", 1) != 0) {
		warning("MVEDecoder::loadStream: Invalid stream header");
		return false;
	}

	_stream->skip(6);

	readNextPacket();

	return true;
}

void MVEDecoder::readNextPacket() {
	while (_stream->pos() < _stream->size()) {
		uint16 size = _stream->readUint16LE();
		uint16 type = _stream->readUint16LE();

debug("Chunk type %d, size %d", type, size);

		switch(type) {
		case kChunkInitializeAudio:
			debug("Initialize Audio");
			break;
		case kChunkAudio:
			debug("Audio Chunk");
			break;
		case kChunkInitializeVideo:
			debug("Initialize Video");
			break;
		case kChunkVideo:
			debug("Video Chunk");
			break;
		case kChunkShutdown:
			debug("Shutdown");
			break;
		case kChunkEnd:
			// End Chunk
			debug("End");
			break;
		default:
			warning("MVEDecoder::readNextChunk: Unknown chunk type %d", type);
			break;
		}

		Common::SeekableReadStream *chunk = _stream->readStream(size);

		parseChunk(chunk);

		if (type == kChunkVideo)
			return;
	}

	if (_stream->pos() >= _stream->size()) {
		if (_videoTrack)
			_videoTrack->setEndOfTrack();
		if (_audioTrack)
			_audioTrack->setEndOfTrack();
	}
}

void MVEDecoder::parseChunk(Common::SeekableReadStream *chunk) {
	while (chunk->pos() < chunk->size()) {
		uint16 size = chunk->readUint16LE();
		byte opcode = chunk->readByte();
		byte version = chunk->readByte();

		int32 nextOpcode = chunk->pos() + size;

		switch(opcode) {
		case kOpcodeEndOfStream:
			debug("kOpcodeEndOfStream");
			return;

		case kOpcodeEndOfChunk:
			debug("kOpcodeEndOfChunk");
			return;

		case kOpcodeCreateTimer: {
			debug("kOpcodeCreateTimer");

			uint32 timerRate = chunk->readUint32LE();
			uint16 timerSubdivision = chunk->readUint16LE();

			Common::Rational frameRate(1000000 * timerSubdivision, timerRate);
			frameRate.debugPrint(0);

			//_videoTrack = new MVEDecoder::MVEVideoTrack(_videoWidth, _videoHeight, frameRate);
			//addTrack(_videoTrack);



			break;
		}
			
		case kOpcodeInitializeAudioBuffers:
			debug("kOpcodeInitialzeAudioBufers");
			break;

		case kOpcodeStartStopAudio:
			debug("kOpcodeStartStopAudio");
			break;

		case kOpcodeInitializeVideoBuffers:
			debug(5, "kOpcodeInitializeVideoBuffers");
			// I'm not sure how to use this information
			// WORD width
			// WORD height
			// WORD ?count?     ; version 1 and 2
			// WORD true-color  ; version 2
			break;

		case kOpcodeUnknown6:
			debug("kOpcodeUnknown6");
			break;

		case kOpcodeSendBufferToDisplay:
			debug("kOpcodeSendBufferToDisplay");
			break;

		case kOpcodeAudioFrameData:
			debug("kOpcodeAudioFrameData");
			break;

		case kOpcodeAudioFrameSilence:
			debug("kOpcodeAudioFrameSilence");
			break;

		case kOpcodeInitializeVideoMode: {
			debug(5, "kOpcodeInitializeVideoMode");
			_videoWidth = chunk->readUint16LE();
			_videoHeight = chunk->readUint16LE();
			// _videoFlags = chunk->readUint16LE();
			break;
		}

		case kOpcodeCreateGradient:
			debug("kOpcodeCreateGradient");
			break;

		case kOpcodeSetPalette: {
			debug(5, "kOpcodeSetPalette");

			byte palette[3 * 256];

			uint16 palStart = chunk->readUint16LE();
			uint16 palCount = chunk->readUint16LE();

			for (uint16 i = 0; i < palCount * 3; i++) {
				int c = chunk->readByte();
				palette[3 * palStart + i] = (c * 255) / 63;
			}

			break;
		}

		case kOpcodeSetPaletteEntriesCompressed:
			debug("kOpcodeSetPaletteEntriesCompressed");
			break;

		case kOpcodeUnknown14:
			debug("kOpcodeUnknown14");
			break;

		case kOpcodeSetDecodingMap:
			debug("kOpcodeSetDecodingMap");
			break;

		case kOpcodeUnknown16:
			debug("kOpcodeUnknown16");
			break;

		case kOpcodeVideoData:
			debug("kOpcodeVideoData");
			break;

		case kOpcodeUnknown18:
			debug("kOpcodeUnknown18");
			break;

		case kOpcodeUnknown19:
			debug("kOpcodeUnknown19");
			break;

		case kOpcodeUnknown20:
			debug("kOpcodeUnknown20");
			break;

		case kOpcodeUnknown21:
			debug("kOpcodeUnknown21");
			break;

		default:
			warning("MVEDecoder::readNextPacket: Unknown opcode %d", opcode);
			break;
		}

		chunk->seek(nextOpcode, SEEK_SET);
	}
}

MVEDecoder::MVEAudioTrack::MVEAudioTrack(Audio::Mixer::SoundType soundType) : MVEDecoder::MVETrack(), AudioTrack(soundType) {
}

MVEDecoder::MVEVideoTrack::MVEVideoTrack(uint16 width, uint16 height, Common::Rational frameRate) : MVEDecoder::MVETrack(), FixedRateVideoTrack() {
	_surface = new Graphics::Surface();
	_surface->create(width, height, Graphics::PixelFormat::createFormatCLUT8());
	_frameRate = frameRate;

	memset(_palette, 0, 3 * 256);
	_curFrame = 0;
}

MVEDecoder::MVEVideoTrack::~MVEVideoTrack() {
	_surface->free();
	delete _surface;
}

} // End of namespace Video
