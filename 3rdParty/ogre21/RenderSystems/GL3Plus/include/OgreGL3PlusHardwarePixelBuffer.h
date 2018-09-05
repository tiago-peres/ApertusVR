/*
  -----------------------------------------------------------------------------
  This source file is part of OGRE
  (Object-oriented Graphics Rendering Engine)
  For the latest info, see http://www.ogre3d.org/

Copyright (c) 2000-2014 Torus Knot Software Ltd

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in
  all copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
  THE SOFTWARE.
  -----------------------------------------------------------------------------
*/

#ifndef __GL3PlusHardwarePixelBuffer_H__
#define __GL3PlusHardwarePixelBuffer_H__

#include "OgreGL3PlusPrerequisites.h"
#include "OgreHardwarePixelBuffer.h"

namespace Ogre {
namespace v1 {
    class _OgreGL3PlusExport GL3PlusHardwarePixelBuffer: public HardwarePixelBuffer
    {
    protected:
        /// Lock a box
        PixelBox lockImpl(const Image::Box &lockBox, LockOptions options);

        /// Unlock a box
        void unlockImpl(void);

        // Internal buffer; either on-card or in system memory, freed/allocated on demand
        // depending on buffer usage
        PixelBox mBuffer;
        GLenum mGLInternalFormat; // GL internal format
        LockOptions mCurrentLockOptions;

        // Buffer allocation/freeage
        void allocateBuffer( size_t bytes );

        void freeBuffer();

        /// Upload a box of pixels to this buffer on the card
        virtual void upload(const PixelBox &data, const Image::Box &dest);

        /// Download a box of pixels from the card
        virtual void download(const PixelBox &data);

    public:
        /// Should be called by HardwareBufferManager
            GL3PlusHardwarePixelBuffer(uint32 mWidth, uint32 mHeight, uint32 mDepth,
                                   PixelFormat mFormat, bool hwGamma,
                                   HardwareBuffer::Usage usage);

        /// @copydoc HardwarePixelBuffer::blitFromMemory
        void blitFromMemory(const PixelBox &src, const Image::Box &dstBox);

        /// @copydoc HardwarePixelBuffer::blitToMemory
        void blitToMemory(const Image::Box &srcBox, const PixelBox &dst);

        ~GL3PlusHardwarePixelBuffer();

        /** Bind surface to frame buffer. Needs FBO extension.
         */
            virtual void bindToFramebuffer(GLenum attachment, uint32 zoffset);
        GLenum getGLFormat() { return mGLInternalFormat; }
    };

    /** Renderbuffer surface.  Needs FBO extension.
     */
    class _OgreGL3PlusExport GL3PlusRenderBuffer: public GL3PlusHardwarePixelBuffer
    {
    public:
            GL3PlusRenderBuffer(GLenum format, uint32 width, uint32 height, GLsizei numSamples);
        ~GL3PlusRenderBuffer();

        /// @copydoc GL3PlusHardwarePixelBuffer::bindToFramebuffer
            virtual void bindToFramebuffer(GLenum attachment, uint32 zoffset);

    protected:
        // In case this is a render buffer
        GLuint mRenderbufferID;
    };
}
}
#endif