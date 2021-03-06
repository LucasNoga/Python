// qbackendnode.sip generated by MetaSIP
//
// This file is part of the Qt3DCore Python extension module.
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


namespace Qt3DCore
{
%TypeHeaderCode
#include <qbackendnode.h>
%End

    class QBackendNodeMapper
    {
%TypeHeaderCode
#include <qbackendnode.h>
%End

    public:
        virtual ~QBackendNodeMapper();
        virtual Qt3DCore::QBackendNode *create(const Qt3DCore::QNodeCreatedChangeBasePtr &change) const = 0 /Factory/;
        virtual Qt3DCore::QBackendNode *get(Qt3DCore::QNodeId id) const = 0;
        virtual void destroy(Qt3DCore::QNodeId id) const = 0;
    };

    class QBackendNode
    {
%TypeHeaderCode
#include <qbackendnode.h>
%End

    public:
        enum Mode
        {
            ReadOnly,
            ReadWrite,
        };

        explicit QBackendNode(Qt3DCore::QBackendNode::Mode mode = Qt3DCore::QBackendNode::Mode::ReadOnly);
        virtual ~QBackendNode();
        Qt3DCore::QNodeId peerId() const;
        void setEnabled(bool enabled);
        bool isEnabled() const;
        Qt3DCore::QBackendNode::Mode mode() const;

    protected:
        void notifyObservers(const Qt3DCore::QSceneChangePtr &e);
        virtual void sceneChangeEvent(const Qt3DCore::QSceneChangePtr &e);

    private:
        QBackendNode(const QBackendNode &);
    };
};
