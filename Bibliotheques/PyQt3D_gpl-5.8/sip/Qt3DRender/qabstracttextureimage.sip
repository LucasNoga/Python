// qabstracttextureimage.sip generated by MetaSIP
//
// This file is part of the Qt3DRender Python extension module.
//
// Copyright (c) 2017 Riverbank Computing Limited <info@riverbankcomputing.com>
// 
// This file is part of PyQt3D.
// 
// This file may be used under the terms of the GNU General Public License
// version 3.0 as published by the Free Software Foundation and appearing in
// the file LICENSE included in the packaging of this file.  Please review the
// following information to ensure the GNU General Public License version 3.0
// requirements will be met: http://www.gnu.org/copyleft/gpl.html.
// 
// If you do not wish to use this file under the terms of the GPL version 3.0
// then you may purchase a commercial license.  For more information contact
// info@riverbankcomputing.com.
// 
// This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
// WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.


namespace Qt3DRender
{
%TypeHeaderCode
#include <qabstracttextureimage.h>
%End

    class QAbstractTextureImage : Qt3DCore::QNode /Abstract/
    {
%TypeHeaderCode
#include <qabstracttextureimage.h>
%End

    public:
        explicit QAbstractTextureImage(Qt3DCore::QNode *parent /TransferThis/ = 0);
        virtual ~QAbstractTextureImage();
        int mipLevel() const;
        int layer() const;
        Qt3DRender::QAbstractTexture::CubeMapFace face() const;

    public slots:
        void setMipLevel(int level);
        void setLayer(int layer);
        void setFace(Qt3DRender::QAbstractTexture::CubeMapFace face);

    signals:
        void mipLevelChanged(int mipLevel);
        void layerChanged(int layer);
        void faceChanged(Qt3DRender::QAbstractTexture::CubeMapFace face);

    protected:
        void notifyDataGeneratorChanged();
        virtual Qt3DRender::QTextureImageDataGeneratorPtr dataGenerator() const = 0;
    };
};
