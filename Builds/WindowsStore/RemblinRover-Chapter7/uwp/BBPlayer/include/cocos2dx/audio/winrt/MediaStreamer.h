//// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
//// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
//// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
//// PARTICULAR PURPOSE.
////
//// Copyright (c) Microsoft Corporation. All rights reserved

#pragma once

#include <wrl.h>
#include <xaudio2.h>
#include <vector>

ref class MediaStreamer
{
private:
	WAVEFORMATEX      m_waveFormat;
	uint32            m_maxStreamLengthInBytes;
	std::vector<byte> m_data;
	UINT32            m_offset;
	UINT32            m_dataLen;
	Platform::String^      m_filename;

	Platform::Array<byte>^ ReadData(_In_ Platform::String^ filename);
	Platform::Array<byte>^ ReadData(_In_ Platform::String^ filename, uint32 from, uint32 length);

internal:
	Windows::Storage::StorageFolder^ m_location;
	Platform::String^ m_locationPath;

public:
	virtual ~MediaStreamer();

internal:
	MediaStreamer();

	WAVEFORMATEX& GetOutputWaveFormatEx()
	{
		return m_waveFormat;
	}

	UINT32 GetMaxStreamLengthInBytes()
	{
		return m_dataLen;
	}

	void Initialize(_In_ const WCHAR* url, bool lazy = false);
	void ReadAll(uint8* buffer, uint32 maxBufferSize, uint32* bufferLength);
	void ReadChunk(uint8* buffer, uint32 from, uint32 length, uint32* bytesRead);
	void Restart();
};
