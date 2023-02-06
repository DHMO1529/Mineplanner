#include "MinePlanner/GlobalConfig.hpp"

#include <sstream>
#include "MinePlanner/GlobalConfigEnumDef.hpp"

//監視者
#include "MinePlanner/Operation/ArrangementManager.hpp"
#include "MinePlanner/Operation/Manager.hpp"
#include "MinePlanner/UI/MainWindow.hpp"
#include "MinePlanner/UI/RepaintOpenGL.hpp"
namespace MinePlanner{
class GlobalConfigImpl
	: public GlobalConfig,
	  public Value::Listener
{
public:
	GlobalConfigImpl();

	virtual void clear();
	virtual std::string toString()const;

	virtual Value& getSliceModeEnableValueObject();
	virtual Value& getModeValueObject();
	virtual Value& getSliceHeightValueObject();
	virtual Value& getUpBlockEnableValueObject();
	virtual Value& getDownBlockEnableValueObject();
	virtual Value& getBlockContourEnableValueObject();
	virtual Value& getLightEnableValueObject();
	virtual Value& getCameraModeValueObject();
	virtual Value& getEditTypeValueObject();
	virtual Value& getSelectBlockValueObject();
	virtual Value& getEditGridEnableValueObject();
	virtual Value& getEditGridHeightValueObject();
	virtual Value& getSubModeValueObject();

	virtual int getMode()const;
	virtual bool getSliceModeEnable()const;
	virtual int getSliceHeight()const;
	virtual bool getUpBlockEnable()const;
	virtual bool getDownBlockEnable()const;
	virtual bool getBlockContourEnable()const;
	virtual bool getLightEnable()const;
	virtual int getCameraMode()const;
	virtual int getEditType()const;
	virtual int getSelectBlock()const;
	virtual bool getEditGridEnable()const;
	virtual int getEditGridHeight()const;
	virtual int getSubMode()const;

	virtual void valueChanged(Value& value);
private:
	Value m_mode;//int
	Value m_sliceModeEnable;//bool
	Value m_sliceHeight;//double
	Value m_upBlockEnable;//bool
	Value m_downBlockEnable;//bool
	Value m_blockContourEnable;//bool
	Value m_lightEnable;//bool
	Value m_cameraMode;//int
	Value m_editType;//int
	Value m_selectBlock;//int
	Value m_editGridEnable;//bool
	Value m_editGridHeight;//double
	Value m_subMode;//int
};

GlobalConfig* getGlobalConfigInstance()
{
	static GlobalConfigImpl instance;
	return &instance;
}

void GlobalConfigImpl::clear()
{
	m_mode.setValue((int)(MODE_VIEW));
	m_sliceModeEnable.setValue((bool)false);
	m_sliceHeight.setValue((double)0.0);
	m_upBlockEnable.setValue((bool)true);
	m_downBlockEnable.setValue((bool)true);
	m_blockContourEnable.setValue((bool)true);
	m_lightEnable.setValue((bool)true);
	m_cameraMode.setValue((int)CAMERA_MODE_NORMAL);
	m_editType.setValue((int)EDITTYPE_ADD);
	m_selectBlock.setValue((int)24 + 1);
	m_editGridEnable.setValue((bool)true);
	m_editGridHeight.setValue((double)0.0);
	m_subMode.setValue((int)SUBMODE_BASIC);
}
std::string GlobalConfigImpl::toString()const
{
	std::stringstream ss;
	ss << "GlobalConfigData info" << std::endl;
	ss << "isViewMode=" << (int)m_mode.getValue() << std::endl;
	ss << "sliceModeEnable=" << (bool)m_sliceModeEnable.getValue() << std::endl;
	ss << "sliceHeight=" << (double)m_sliceHeight.getValue() << std::endl;
	ss << "upBlockEnable=" << (bool)m_upBlockEnable.getValue() << std::endl;//上下ブロックを表示する？
	ss << "downBlockEnable=" << (bool)m_downBlockEnable.getValue() << std::endl;
	ss << "blockContourEnable=" << (bool)m_blockContourEnable.getValue() << std::endl;
	ss << "lightEnable=" << (bool)m_lightEnable.getValue() << std::endl;
	ss << "isNormalCamera=" << (int)m_cameraMode.getValue() << std::endl;
	ss << "editType=" << (int)m_editType.getValue() << std::endl;
	ss << "selectBlock=" << (int)m_selectBlock.getValue() << std::endl;
	ss << "editGridEnable=" << (bool)m_editGridEnable.getValue() << std::endl;
	ss << "editGridHeight=" << (double)m_editGridHeight.getValue() << std::endl;
	ss << "subMode=" << (int)m_subMode.getValue() << std::endl;
	return ss.str();
}

GlobalConfigImpl::GlobalConfigImpl()
{
	m_mode.addListener(this);
	m_sliceModeEnable.addListener(this);
	m_sliceHeight.addListener(this);
	m_upBlockEnable.addListener(this);
	m_downBlockEnable.addListener(this);
	m_blockContourEnable.addListener(this);
	m_lightEnable.addListener(this);
	m_cameraMode.addListener(this);
	m_editType.addListener(this);
	m_selectBlock.addListener(this);
	m_editGridEnable.addListener(this);
	m_editGridHeight.addListener(this);

	this->clear();
}
Value& GlobalConfigImpl::getSliceModeEnableValueObject()
{
	return m_sliceModeEnable;
}
Value& GlobalConfigImpl::getModeValueObject()
{
	return m_mode;
}
Value& GlobalConfigImpl::getSliceHeightValueObject()
{
	return m_sliceHeight;
}
Value& GlobalConfigImpl::getUpBlockEnableValueObject()
{
	return m_upBlockEnable;
}
Value& GlobalConfigImpl::getDownBlockEnableValueObject()
{
	return m_downBlockEnable;
}
Value& GlobalConfigImpl::getBlockContourEnableValueObject()
{
	return m_blockContourEnable;
}
Value& GlobalConfigImpl::getLightEnableValueObject()
{
	return m_lightEnable;
}
Value& GlobalConfigImpl::getCameraModeValueObject()
{
	return m_cameraMode;
}
Value& GlobalConfigImpl::getEditTypeValueObject()
{
	return m_editType;
}
Value& GlobalConfigImpl::getSelectBlockValueObject()
{
	return m_selectBlock;
}
Value& GlobalConfigImpl::getEditGridEnableValueObject()
{
	return m_editGridEnable;
}
Value& GlobalConfigImpl::getEditGridHeightValueObject()
{
	return m_editGridHeight;
}
Value& GlobalConfigImpl::getSubModeValueObject()
{
	return m_subMode;
}
void GlobalConfigImpl::valueChanged(Value& value)
{
	if(m_mode.refersToSameSourceAs(value))
	{
		g_pArrangementManager()->onModeChanged();
		UI::updateMenuBar();
	}

	UI::RepaintOpenGL();
}
int GlobalConfigImpl::getMode()const
{
	return static_cast<int>(m_mode.getValue());
}
bool GlobalConfigImpl::getSliceModeEnable()const
{
	return static_cast<bool>( m_sliceModeEnable.getValue() );
}
int GlobalConfigImpl::getSliceHeight()const
{
	return static_cast<int>(static_cast<double>(m_sliceHeight.getValue()));
}
bool GlobalConfigImpl::getUpBlockEnable()const
{
	return static_cast<bool>(m_upBlockEnable.getValue());
}
bool GlobalConfigImpl::getDownBlockEnable()const
{
	return static_cast<bool>(m_downBlockEnable.getValue());
}
bool GlobalConfigImpl::getBlockContourEnable()const
{
	return static_cast<bool>(m_blockContourEnable.getValue());
}
bool GlobalConfigImpl::getLightEnable()const
{
	return static_cast<bool>(m_lightEnable.getValue());
}
int GlobalConfigImpl::getCameraMode()const
{
	return static_cast<int>(m_cameraMode.getValue());
}
int GlobalConfigImpl::getEditType()const
{
	return static_cast<int>(m_editType.getValue());
}
int GlobalConfigImpl::getSelectBlock()const
{
	return static_cast<int>(m_selectBlock.getValue()) - 1;
}
bool GlobalConfigImpl::getEditGridEnable()const
{
	return static_cast<bool>(m_editGridEnable.getValue());
}
int GlobalConfigImpl::getEditGridHeight()const
{
	return static_cast<int>( static_cast<double>(m_editGridHeight.getValue()) );
}
int GlobalConfigImpl::getSubMode()const
{
	return static_cast<int>(m_subMode.getValue());
}
}//MinePlanner