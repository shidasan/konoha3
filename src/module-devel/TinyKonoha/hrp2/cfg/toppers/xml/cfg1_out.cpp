/* 
 *  TOPPERS ATK2
 *      Toyohashi Open Platform for Embedded Real-Time Systems
 *      Automotive Kernel Version 2
 *  
 *  Copyright (C) 2007-2012 by TAKAGI Nobuhisa
 *  Copyright (C) 2010 by Meika Sugimoto
 *  Copyright (C) 2011-2012 by Center for Embedded Computing Systems
 *              Graduate School of Information Science, Nagoya Univ., JAPAN
 *  Copyright (C) 2011-2012 by FUJISOFT INCORPORATED, JAPAN
 *  Copyright (C) 2011-2012 by FUJITSU VLSI LIMITED, JAPAN
 *  Copyright (C) 2011-2012 by NEC Communication Systems, Ltd., JAPAN
 *  Copyright (C) 2011-2012 by Panasonic Advanced Technology Development Co., Ltd., JAPAN
 *  Copyright (C) 2011-2012 by Renesas Electronics Corporation, JAPAN
 *  Copyright (C) 2011-2012 by Sunny Giken Inc., JAPAN
 *  Copyright (C) 2011-2012 by TOSHIBA CORPOTATION, JAPAN
 *  Copyright (C) 2011-2012 by Witz Corporation, JAPAN
 *  
 *  �嵭����Ԥϡ��ʲ���(1)��(4)�ξ������������˸¤ꡤ�ܥ��եȥ���
 *  �����ܥ��եȥ���������Ѥ�����Τ�ޤࡥ�ʲ�Ʊ���ˤ���ѡ�ʣ������
 *  �ѡ������ۡʰʲ������ѤȸƤ֡ˤ��뤳�Ȥ�̵���ǵ������롥
 *  (1) �ܥ��եȥ������򥽡��������ɤη������Ѥ�����ˤϡ��嵭������
 *      ��ɽ�����������Ѿ�浪��Ӳ�����̵�ݾڵ��꤬�����Τޤޤη��ǥ���
 *      ����������˴ޤޤ�Ƥ��뤳�ȡ�
 *  (2) �ܥ��եȥ������򡤥饤�֥������ʤɡ�¾�Υ��եȥ�������ȯ�˻�
 *      �ѤǤ�����Ǻ����ۤ�����ˤϡ������ۤ�ȼ���ɥ�����ȡ�����
 *      �ԥޥ˥奢��ʤɡˤˡ��嵭�����ɽ�����������Ѿ�浪��Ӳ���
 *      ��̵�ݾڵ����Ǻܤ��뤳�ȡ�
 *  (3) �ܥ��եȥ������򡤵�����Ȥ߹���ʤɡ�¾�Υ��եȥ�������ȯ�˻�
 *      �ѤǤ��ʤ����Ǻ����ۤ�����ˤϡ����Τ����줫�ξ�����������
 *      �ȡ�
 *    (a) �����ۤ�ȼ���ɥ�����ȡ����Ѽԥޥ˥奢��ʤɡˤˡ��嵭����
 *        �ɽ�����������Ѿ�浪��Ӳ�����̵�ݾڵ����Ǻܤ��뤳�ȡ�
 *    (b) �����ۤη��֤��̤�������ˡ�ˤ�äơ�TOPPERS�ץ������Ȥ�
 *        ��𤹤뤳�ȡ�
 *  (4) �ܥ��եȥ����������Ѥˤ��ľ��Ū�ޤ��ϴ���Ū�������뤤���ʤ�»
 *      ������⡤�嵭����Ԥ����TOPPERS�ץ������Ȥ����դ��뤳�ȡ�
 *      �ޤ����ܥ��եȥ������Υ桼���ޤ��ϥ���ɥ桼������Τ����ʤ���
 *      ͳ�˴�Ť����ᤫ��⡤�嵭����Ԥ����TOPPERS�ץ������Ȥ�
 *      ���դ��뤳�ȡ�
 *  
 *  �ܥ��եȥ������ϡ�̵�ݾڤ��󶡤���Ƥ����ΤǤ��롥�嵭����Ԥ�
 *  ���TOPPERS�ץ������Ȥϡ��ܥ��եȥ������˴ؤ��ơ�����λ�����Ū
 *  ���Ф���Ŭ������ޤ�ơ������ʤ��ݾڤ�Ԥ�ʤ����ޤ����ܥ��եȥ���
 *  �������Ѥˤ��ľ��Ū�ޤ��ϴ���Ū�������������ʤ�»���˴ؤ��Ƥ⡤��
 *  ����Ǥ�����ʤ���
 * 
 *  $Id: cfg1_out.cpp 133 2012-12-18 04:30:30Z ertl-hiro $
 */

#include <cstdlib>
#include <cerrno>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iterator>
#include <algorithm>
#include <stack>
#include "toppers/text.hpp"
#include "toppers/diagnostics.hpp"
#include "toppers/c_expr.hpp"
#include "toppers/global.hpp"
#include "toppers/macro_processor.hpp"
#include "toppers/s_record.hpp"
#include "toppers/nm_symbol.hpp"
#include "toppers/misc.hpp"
#include "toppers/xml/cfg1_out.hpp"
#include "toppers/xml/xml_parser.hpp"
#include <boost/spirit/include/classic.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>

/*!
 *  \brief  ���֥�������ID�ֹ�γ��դ�
 *  \param[in]  api_map   �������˵��Ҥ��줿��ŪAPI����Ͽ��������ƥ�
 */
void child_assign_id(toppers::xml::container::object * pObj, int fixed_id)
{
  std::vector<toppers::xml::container::object*>::const_iterator sub;

  if( pObj->getSubcontainers()->size() != 0 )
  {
    for( sub = pObj->getSubcontainers()->begin() ; sub != pObj->getSubcontainers()->end() ; sub++ )
    {
      child_assign_id( *sub, fixed_id );
    }
  }
  if (pObj->getId() == toppers::xml::container::object::undefined)
  {
    pObj->setId( fixed_id );
  }
}
void assign_id( toppers::xml::cfg1_out::xml_obj_map const& xml_map)
{
  std::map<std::string, std::vector<toppers::xml::container::object*> >::const_iterator p;
  std::vector<toppers::xml::container::object*>::const_iterator q;
  std::vector<toppers::xml::container::object*>::const_iterator sub;
  int serial;

  for(p = xml_map.begin() ; p != xml_map.end() ; p++)
  {
    serial = 1;
    // ���֥������Ȥ��Ȥ�ID������
    for(q = (*p).second.begin() ; q != (*p).second.end() ; q++)
    {
      (*q)->setId( serial );
      if((*q)->getSubcontainers()->size() != 0)
      {
        for(sub = (*q)->getSubcontainers()->begin() ; sub != (*q)->getSubcontainers()->end() ; sub++)
        {
          child_assign_id( *sub, serial );
        }
      }
      serial++;
    }
  }

}

//  ʸ������ִ�����
std::string Replace( std::string String1, std::string String2, std::string String3 )
{
    std::string::size_type  Pos( String1.find( String2 ) );

    while( Pos != std::string::npos )
    {
        String1.replace( Pos, String2.length(), String3 );
        Pos = String1.find( String2, Pos + String3.length() );
    }

    return String1;
}

namespace toppers
{
  namespace xml
  {
    //! cfg_out ���饹�μ����ܺ�
    struct cfg1_out::implementation
    {
    protected:
      output_file ofile_;
	  std::vector< toppers::xml::container::object* > container_array_; /*  xml����ѡ����������ǡ��� only xml */
      std::map< std::string, std::string > info_rmap_; /*   xml */

      std::string cfg1_out_list_;
      std::string includes_;

      std::tr1::shared_ptr< s_record > srec_;
      std::tr1::shared_ptr< nm_symbol > syms_;
      bool little_endian_;
      std::size_t base_;
      cfg1_def_table const* def_table_;

      implementation( std::string const& filename, std::ios_base::openmode omode, cfg1_def_table const* def_table = 0 )
        : ofile_( filename, omode ), little_endian_( true ), base_( 1 ), def_table_( def_table )
      {
      }
      virtual ~implementation()
      {
      }
      virtual void validate_type(std::vector< toppers::xml::container::object* > const& objects ,std::map<std::string, toppers::xml::info> const& info_map );
      virtual void validate_multiplicity( toppers::xml::container::object* object ,std::map<std::string, toppers::xml::info> const& info_map );
      virtual string do_out_macro_name(std::vector<toppers::xml::container::parameter*>::const_iterator r, int serial, std::map<std::string, toppers::xml::info> const& info_map);
      virtual string do_search_macro(std::vector< toppers::xml::container::object* > const& objects ,std::map<std::string, toppers::xml::info> const& info_map );
      virtual void do_search_includes(std::vector< toppers::xml::container::object* > const& objects ,std::string include_container, std::list< string > *incstr );
      virtual void do_load_cfg( std::string const& input_file, codeset_t codeset, std::map<std::string, toppers::xml::info> const& info_map );
      virtual void do_generate_includes() const
      {
      }
      virtual void do_generate_cfg1_def() const
      {
        ofile_ << "const uint32 TOPPERS_cfg_magic_number = 0x12345678;\n"
                  "const uint32 TOPPERS_cfg_sizeof_signed_t = sizeof(signed_t);\n"
                  "const uint32 TOPPERS_cfg_sizeof_pointer = sizeof(const volatile void*);\n"
                  "\n";

        if ( def_table_ != 0 )	// ���ͼ�������ܥ�ơ��֥��
        {
          for ( cfg1_def_table::const_iterator iter( def_table_->begin() ), last( def_table_->end() );
                iter != last;
                ++iter )
          {
            // ���κǽ�� # ������С�����ϥޥ��������Ƚ��
            // ����ա� #@ �ǻϤޤ�񼰤��ѻ� 2010/07/23
            bool is_pp = ( iter->expression[ 0 ] == '#' );
            if ( !iter->value1.empty() || !iter->value2.empty() ) // ��CSV�Ρ�4���ܤޤ���5���ܤ��ͤ������...
            {
              is_pp = true;
            }

            std::string type = ( iter->is_signed ? "signed_t" : "unsigned_t" );
            std::string definition = "const " + type + " ";
            definition += "TOPPERS_cfg_" + iter->name;
            if ( is_pp )
            {
              std::string expression = iter->expression.substr( iter->expression[ 0 ] == '#' ? 1 : 0 );
              std::string value1 = ( !iter->value1.empty() ? iter->value1 : "1" );
              std::string value2 = ( !iter->value2.empty() ? iter->value2 : "0" );
              definition +=
                          " = \n"
                          "#if " + expression + "\n"
                          "(" + value1 + ");\n"
                          "#else\n"
                          "(" + value2 + ");\n"
                          "#endif\n";
            }
            else if ( iter->expression[ 0 ] == '@' )  // '@'�ǻϤޤ�Х��ɥ쥹
            {
              definition = "const volatile void* const TOPPERS_cfg_" + iter->name + " = (" + ( iter->expression.c_str() + 1 ) + ");\n";
            }
            else
            {
              definition +=
                          " = ( " + type + " )" + iter->expression + ";\n";
            }
            ofile_ << definition;
          }
        }
      }
      virtual void do_assign_params();
      virtual implementation* do_clone() const
      {
        return new implementation( *this );
      }

      void preprocess( std::string const& input_file, codeset_t codeset, text& txt );

      friend class cfg1_out;
    };

    string cfg1_out::search_info_pathname(string shortname) const
    {
      string result;
      std::map< std::string, std::string >::iterator pInfo = pimpl_->info_rmap_.find(shortname);

      if( pInfo != pimpl_->info_rmap_.end() )
      {
        result = pInfo->second;
      }
      return result;
    }

    /*!
     *  \brief  ���󥹥ȥ饯��
     *  \param[in]  filename    cfg1_out.c �ޤ��� cfg1_out.srec �㤷���Ϥ���������̾
     *  \param[in]  def_table   cfg1_out.c �����Ѥ�����ơ��֥�
     */
    cfg1_out::cfg1_out( std::string const& filename, cfg1_def_table const* def_table )
      : pimpl_( new implementation( filename, std::ios_base::out, def_table ) )
    {
    }

    /*!
     *  \brief  ���ԡ����󥹥ȥ饯��
     *  \param[in]  other   ���ԡ���
     */
    cfg1_out::cfg1_out( cfg1_out const& other )
      : pimpl_( other.pimpl_->do_clone() )
    {
    }

    //! �ǥ��ȥ饯��
    cfg1_out::~cfg1_out()
    {
	  del_containers();
      delete pimpl_;
      pimpl_ = 0;
    }

    /*!
     *  \brief  �����ƥॳ��ե�����졼�����ե�����Υ���
     *  \param[in]  input_file  ���ϥե�����̾
     *  \param[in]  codeset     ʸ��������
     *  \param[in]  obj_info    ���֥������Ⱦ����Ϣ������
     */
    void cfg1_out::load_cfg( std::string const& input_file, codeset_t codeset, 
    		std::map<std::string, toppers::xml::info> const& info_map )
    {
      return pimpl_->do_load_cfg( input_file, codeset, info_map );
    }

    // �ѥ�᡼���η���ECUC-NUMERICAL-PARAM-VALUE�ʤΤ���������ư�������Ǥʤ����ϥޥ���̾�Ȥ��ơ�cfg_out.c�ؽ��Ϥ���
    string cfg1_out::implementation::do_out_macro_name( std::vector< toppers::xml::container::parameter* >::const_iterator pPara, int serial,
      std::map<std::string, toppers::xml::info> const& info_map )
    {
      ostringstream stream;
      if( toppers::xml::container::TYPE_INT == (*pPara)->getType() || toppers::xml::container::TYPE_FLOAT == (*pPara)->getType() )
      {
        string contanerDefName( (*pPara)->getParent()->getDefName() );
        string contanerObjName( (*pPara)->getParent()->getObjName() );
        string paramDefName( (*pPara)->getDefName() );
        string paramValue( (*pPara)->getValue() );
        string grandObjName;
        if( (*pPara)->getParent()->getParent() != NULL )
        {
          grandObjName = (*pPara)->getParent()->getParent()->getObjName();
        }

        std::map<std::string, toppers::xml::info>::const_iterator pInfo = info_map.find(contanerDefName);
        if(pInfo != info_map.end())
        {
          contanerDefName = Replace(contanerDefName, pInfo->first, pInfo->second.tfname);
        }
        pInfo = info_map.find(paramDefName);
        if(pInfo != info_map.end())
        {
          paramDefName = Replace(paramDefName, pInfo->first, pInfo->second.tfname);
        }

        boost::replace_all(contanerDefName, ".", "_");
        boost::replace_all(paramDefName, ".", "_");
        if(toppers::xml::container::TYPE_INT == (*pPara)->getType())
        {
          try
          {
            int value = boost::lexical_cast<int>( paramValue );
          }
          catch( const boost::bad_lexical_cast& e)
          {
            stream << "const unsigned_t TOPPERS_cfg_valueof_" << contanerDefName << "_" << paramDefName << "_" << contanerObjName  << "_" << grandObjName << " = ( " << paramValue << " ); \n";
          }
        }
        else
        {
          try
          {
            float value = boost::lexical_cast<float>( paramValue );
          }
          catch( const boost::bad_lexical_cast& e)
          {
            stream << "const unsigned_t TOPPERS_cfg_valueof_" << contanerDefName << "_" << paramDefName << "_" << contanerObjName  << "_" << grandObjName << " = ( " << paramValue << " ); \n";
          }
        }
      }
      return stream.str();
    }

    string cfg1_out::implementation::do_search_macro(std::vector< toppers::xml::container::object* > const& objects,
      std::map<std::string, toppers::xml::info> const& info_map )
    {
      ostringstream stream;

      for ( std::vector< toppers::xml::container::object* >::const_iterator pObj = objects.begin() ;
        pObj != objects.end();
        ++pObj )
      {
        int serial = 0;
        if( (*pObj)->getSubcontainers()->size() != 0)
        {
          stream << do_search_macro( *(*pObj)->getSubcontainers(), info_map );
        }
        for( std::vector< toppers::xml::container::parameter* >::iterator pPara = (*pObj)->getParams()->begin() ;
          pPara != (*pObj)->getParams()->end();
          ++pPara )
        {
          stream << do_out_macro_name( pPara, serial++, info_map );
        }
      }
      return stream.str();
    }

    /*!
     *  \brief  ���󥯥롼�ɥ���ƥʾ������Ф���
     *  \param[in]  objects  XML�ǥѡ�����������ƥʤ�Ϣ������
     *  \param[in]  include_container ��Ф��륳��ƥʤΥե�ѥ�̾
     */
    void cfg1_out::implementation::do_search_includes(std::vector< toppers::xml::container::object* > const& objects,
        std::string include_container, std::list< string > *incstr )
    {
        ostringstream stream;

        for ( std::vector< toppers::xml::container::object* >::const_iterator pObj = objects.begin() ;
            pObj != objects.end();
            ++pObj )
        {
            if( (*pObj)->getSubcontainers()->size() != 0)
            {
                do_search_includes( *(*pObj)->getSubcontainers(), include_container, incstr );
            }
            for( std::vector< toppers::xml::container::parameter* >::iterator pPara = (*pObj)->getParams()->begin() ;
                pPara != (*pObj)->getParams()->end();
                ++pPara )
            {
                if( (*pPara)->getDefName() == include_container )
                    (*incstr).push_back( (*pPara)->getValue() );
            }
        }
        return ;
    }

    /*! 
     *  \brief  ¿���پ���򸡾ڤ��� 
     *  \param[in]  objects  XML�ǥѡ�����������ƥʤ�Ϣ������ 
     *  \param[in]  info_map ATK2�ǻ��ꤹ�륳��ƥʾ����Ϣ������ 
     */ 
    void cfg1_out::implementation::validate_multiplicity( toppers::xml::container::object* object,
      std::map<std::string, toppers::xml::info> const& info_map )
    {
      std::string objPath( object->getDefName() );
      std::map<std::string, toppers::xml::info> search_map;
      std::map<std::string, unsigned int> multi_map;

      // ������ƥʤΥѥ�᡼���ȥ��֥���ƥʤ�¿������������info_map�����������
      for( std::map<std::string, toppers::xml::info>::const_iterator pInfo = info_map.begin() ;
        pInfo != info_map.end() ;
        ++pInfo )
      {
        // objPath��Ʊ��ʸ���󤬤�����ʸ�ˤĤŤ��ѥ������äƤ�褤��
        if( pInfo->first.find(objPath) != string::npos )
        {
          // objPath�Τ��Ȥ�³��ʸ��������
          std::string str( pInfo->first.substr(objPath.size()) );
          // str�Υѥ�����1�Ĥ����ʤ����ϼ�����ƥʤΥѥ�᡼�������֥���ƥʤǤ���
          if( 0 == (int)str.rfind("/") )
          {
            search_map.insert(make_pair(pInfo->first, pInfo->second ));
          }
        }
      }

      // ������ƥʤΥѥ�᡼����¿���٤򽸷פ���
      for ( std::vector<toppers::xml::container::parameter*>::const_iterator pPara = object->getParams()->begin() ;
        pPara != object->getParams()->end();
        ++pPara )
      {
        std::map<std::string, unsigned int>::iterator pMulti = multi_map.find( (*pPara)->getDefName() );
        if(pMulti == multi_map.end())
        {
          multi_map.insert( make_pair((*pPara)->getDefName(), 1) );
        }
        else
        {
          pMulti->second++;
        }
      }
      // ������ƥʤΥ��֥���ƥʤ�¿���٤򽸷פ���
      for ( std::vector< toppers::xml::container::object* >::iterator pObj = object->getSubcontainers()->begin() ;
        pObj != object->getSubcontainers()->end();
        ++pObj )
      {
        std::map<std::string, unsigned int>::iterator pMulti = multi_map.find( (*pObj)->getDefName() );
        if(pMulti == multi_map.end())
        {
          multi_map.insert( make_pair((*pObj)->getDefName(), 1) );
        }
        else
        {
          pMulti->second++;
        }
      }

      // ¿���پ��������å�����
      for (  std::map<std::string, toppers::xml::info>::const_iterator pSearch = search_map.begin() ;
        pSearch != search_map.end();
        ++pSearch )
      {
        std::map<std::string, unsigned int>::iterator pMulti = multi_map.find( pSearch->first );
        if(pMulti == multi_map.end())
        {
          if( pSearch->second.multimin > 0)
          {
            fatal( _("`%1%\' is not exist.") ,pSearch->first );
          }
        }
        else
        {
          if( pSearch->second.multimin > pMulti->second  || pSearch->second.multimax < pMulti->second )
          {
            fatal( _("`%1%\' multiplicity is out of range. This multiplicity is `%2%'.") ,pSearch->first ,pMulti->second );
          }
        }
      }
      
      // ���֥���ƥʤΥ����å���Ԥ�
      for (  std::vector<toppers::xml::container::object*>::const_iterator pSub = object->getSubcontainers()->begin() ;
        pSub != object->getSubcontainers()->end();
        ++pSub )
      {
        validate_multiplicity(*pSub, info_map);
      }
    }

    /*!
     *  \brief  ����ƥʤΥѥ�᡼���η�����򸡾ڤ���
     *  \param[in]  objects  XML�ǥѡ�����������ƥʤ�Ϣ������
     *  \param[in]  info_map ATK2�ǻ��ꤹ�륳��ƥʾ����Ϣ������
     */
    void cfg1_out::implementation::validate_type(std::vector< toppers::xml::container::object* > const& objects,
      std::map<std::string, toppers::xml::info> const& info_map )
    {
      for ( std::vector< toppers::xml::container::object* >::const_iterator pObj = objects.begin() ;
        pObj != objects.end();
        ++pObj )
      {
        for(std::vector< toppers::xml::container::parameter* >::const_iterator pPara = (*pObj)->getParams()->begin() ;
          pPara != (*pObj)->getParams()->end();
          ++pPara )
        {
          std::map<std::string, toppers::xml::info>::const_iterator pInfo = info_map.find( (*pPara)->getDefName() );
          if( pInfo == info_map.end() )
          {
            warning( _( "Unknown Parameter(%1%:%2%) : `%3%\'. " ), (*pPara)->getFileName(), (*pPara)->getLine(), (*pPara)->getDefName() );
            (*pPara)->setType(toppers::xml::container::TYPE_UNKNOWN);
          }
          else
          {
            // ���ξ��
            if('+' == pInfo->second.type[0])
            {
                (*pPara)->setType( pInfo->second.type_enum ) ;
            }
            // �ѥ�᡼���η������å�
            else if( (*pPara)->getType() != pInfo->second.type_enum )
            {
              int line = (*pPara)->getLine();
              fatal( _( "Parameter type miss match(%1%:%2%) : `%3%\' is not `%4%\' type. " ), (*pPara)->getFileName(), (*pPara)->getLine(), (*pPara)->getDefName(), pInfo->second.type );
            }
          }
        }
        // ���֥���ƥʤ�������
         for (  std::vector<toppers::xml::container::object*>::iterator pSub = (*pObj)->getSubcontainers()->begin() ;
          pSub != (*pObj)->getSubcontainers()->end();
          ++pSub )
        {
          validate_type( *(*pObj)->getSubcontainers(), info_map );
        }
      }
    }

    /*!
     *  \brief  �����ƥॳ��ե�����졼�����ե�����Υ��ɽ����μ���
     *  \param[in]  input_file  ���ϥե�����̾
     *  \param[in]  codeset     ʸ��������
     *  \param[in]  obj_info    ���֥������Ⱦ����Ϣ������
     */
    void cfg1_out::implementation::do_load_cfg( std::string const& input_file, 
                codeset_t codeset, std::map<std::string, toppers::xml::info> const& info_map )
    {
      // XML�ե�����Υѡ�������
      std::vector< toppers::xml::container::object*> container_array_temp( xml_parser_init(input_file) );

      // ���󥯥롼�ɥ���ƥʤΥե�ѥ�̾�����
      std::string include_container;
      std::string s1;
      for( std::map<std::string, toppers::xml::info>::const_iterator pInfo = info_map.begin() ;
          pInfo != info_map.end() ;
          ++pInfo)
      {
          s1 = pInfo->second.type;
          if(s1.find("INCLUDE", 0 ) != string::npos)
              include_container = pInfo->first;
      }
      if ( include_container.empty() )
        include_container = "/AUTOSAR/EcucDefs/Os/OsInclude/OsIncludeFileName";

      //���󥯥롼�ɥ���ƥʾ�������
      std::list< string > incstr;
      do_search_includes( container_array_temp, include_container, &incstr );

      std::ostringstream oss, includes_oss;
      std::list< string >::iterator pIncStr = incstr.begin();
      while( pIncStr != incstr.end() )
      {
        oss << "/* #include \"" << *pIncStr << "\" */\n";
        includes_oss << "#include \"" << *pIncStr << "\"\n";

        ++pIncStr;
      }

      // ¿���٤θ���
      toppers::xml::container::object *obj = new toppers::xml::container::object();
      obj->setSubcontainers(container_array_temp);
      std::string container_path( get_global_string( "XML_ContainerPath" ) );
      if ( container_path.empty() )
        container_path = "/AUTOSAR/EcucDefs";
      obj->setDefName( container_path );
      validate_multiplicity(obj, info_map);

      // ������θ���
      for ( std::vector< toppers::xml::container::object* >::iterator pObj = container_array_temp.begin() ;
        pObj != container_array_temp.end();
        ++pObj )
      {
        validate_type(*(*pObj)->getSubcontainers(), info_map);
      }

      // api-table��û��̾��URI̾��Ϣ������(info_rmap_)�����
      for( std::map<std::string, toppers::xml::info>::const_iterator pInfo = info_map.begin() ;
        pInfo != info_map.end() ;
        ++pInfo)
      {
        info_rmap_.insert( pair<std::string, std::string>(pInfo->second.tfname, pInfo->first));
      }

      // XML�ѡ����Υѥ�᡼���ǥޥ���ˤʤäƤ����Τ���Ϥ���
      oss << do_search_macro(container_array_temp, info_map);
          
      // �ǡ������Фؤ�ȿ��
      std::string cfg1_list_temp( oss.str() );
      std::string includes_temp( includes_oss.str() );

      cfg1_out_list_.swap( cfg1_list_temp );
      container_array_.swap(container_array_temp);
      includes_.swap( includes_temp );
    }

    /*!
     *  \brief  cfg1_out.c ����������
     *  \param[in]  type  ���� cfg1_out[] �����Ƿ������ݥ��󥿤ξ��� uint32_t �Ȥ��ư����롣
     */
    void cfg1_out::generate( char const* type ) const
    {
      if ( type == 0 )
      {
        type = "uint32_t";
      }
      pimpl_->ofile_ << "/* cfg1_out.c */\n"
                        "#define TOPPERS_CFG1_OUT  1\n" 
                        "#include \"kernel/kernel_int.h\"\n";
      pimpl_->do_generate_includes();
      pimpl_->ofile_ << pimpl_->includes_ << '\n';

      // int128_t�ϸΰդ�̵��
      // int128_t��·����Ƚ������Ť��ʤꤹ���뤿��
      pimpl_->ofile_ << "\n#ifdef INT64_MAX\n"
                        "  typedef sint64 signed_t;\n"
                        "  typedef uint64 unsigned_t;\n"
                        "#else\n"
                        "  typedef sint32 signed_t;\n"
                        "  typedef uint32 unsigned_t;\n"
                        "#endif\n";

      pimpl_->ofile_ << "\n#include \"target_cfg1_out.h\"\n\n";

      pimpl_->do_generate_cfg1_def();
      pimpl_->ofile_ << pimpl_->cfg1_out_list_ << '\n';
    }

    /*!
     *  \brief  #include������¤Ӥ��������
     *  \return #include������¤�
     *
     *  ���Υ��дؿ��ϡ�
     *  \code
     *  #include <...>
     *  #include "..."
     *  \endcode
     *  �Ȥ��ä�#include������¤Ӥ�ʸ����Ȥ����֤���
     */
    std::string const& cfg1_out::get_includes() const
    {
      return pimpl_->includes_;
    }

    /*!
     *  \brief  S�쥳���ɤΥ���
     */
    void cfg1_out::load_srec()
    {
      std::ifstream srec_ifs( ( pimpl_->ofile_.file_name() + ".srec" ).c_str() );
      if ( !srec_ifs.is_open() )
      {
        fatal( _( "cannot open file `%1%\'" ), pimpl_->ofile_.file_name() + ".srec" );
      }
      pimpl_->srec_ = std::tr1::shared_ptr< s_record >( new s_record( srec_ifs ) );

      std::ifstream syms_ifs( ( pimpl_->ofile_.file_name() + ".syms" ).c_str() );
      if ( !syms_ifs.is_open() )
      {
        fatal( _( "cannot open file `%1%\'" ), pimpl_->ofile_.file_name() + ".syms" );
      }
      pimpl_->syms_ = std::tr1::shared_ptr< nm_symbol >( new nm_symbol( syms_ifs ) );

      nm_symbol::entry nm_entry = pimpl_->syms_->find( "TOPPERS_cfg_magic_number" );
      if ( nm_entry.type < 0 )
      {
        fatal( _( "magic number is not found in `%1%\'" ), ( pimpl_->ofile_.file_name() + ".srec/.syms" ) );
      }
      unsigned long magic[ 4 ];
      magic[ 0 ] = ( *pimpl_->srec_ )[ nm_entry.address + 0 ];
      magic[ 1 ] = ( *pimpl_->srec_ )[ nm_entry.address + 1 ];
      magic[ 2 ] = ( *pimpl_->srec_ )[ nm_entry.address + 2 ];
      magic[ 3 ] = ( *pimpl_->srec_ )[ nm_entry.address + 3 ];
      unsigned long magic_number = ( magic[ 0 ] << 24 ) | ( magic[ 1 ] << 16 ) | ( magic[ 2 ] << 8 ) | magic[ 3 ];
      if ( magic_number == 0x12345678 )
      {
        pimpl_->little_endian_ = false;
      }
      else if ( magic_number == 0x78563412 )
      {
        pimpl_->little_endian_ = true;
      }
      else
      {
        fatal( _( "magic number is not found in `%1%\'" ), ( pimpl_->ofile_.file_name() + ".srec/.syms" ) );
      }
      pimpl_->do_assign_params();
    }

    /*!
     *  \brief  "cfg1_out.srec" �����ɤ߼�ä�����λ���
     */
    std::tr1::shared_ptr< s_record > cfg1_out::get_srec() const
    {
      return pimpl_->srec_;
    }

    /*!
     *  \brief  "cfg1_out.syms" �����ɤ߼�ä�����λ���
     */
    std::tr1::shared_ptr< nm_symbol > cfg1_out::get_syms() const
    {
      return pimpl_->syms_;
    }

    cfg1_out::cfg1_def_table const* cfg1_out::get_def_table() const
    {
      return pimpl_->def_table_;
    }



    cfg1_out::xml_obj_map cfg1_out::merge(std::map<std::string, toppers::xml::info> const& info_map ) const
    {
      return do_merge(pimpl_->container_array_, info_map);
    }

    /*!
     *  \brief  ����ƥʤ��Ȥ�XML����ƥʾ����ޤȤ��
     *  \return ����ƥʾ���
     *
     *  ���δؿ��ϡ�"OsOS"��"OsTask"�Ȥ��ä����̤򥭡��Ȥ��ơ����μ��̤�ʬ�व��륳��ƥʾ����Ϣ��������������롣
     */
    void cfg1_out::do_sub_merge(std::vector< toppers::xml::container::object* > objects, xml_obj_map & xml_map,
      std::map<std::string, toppers::xml::info> const& info_map ) const
    {
      for ( std::vector< toppers::xml::container::object* >::iterator pObj = objects.begin() ;
        pObj != objects.end();
        ++pObj )
      {
        if((*pObj)->getSubcontainers()->size() != 0)
        {
          do_sub_merge( *(*pObj)->getSubcontainers(), xml_map, info_map);
        }
        // XML�Υե�ѥ������û��ʸ������֤�������
        string str = replase_xml_pathname(pObj, info_map);
        xml_map[ str ].push_back( *pObj );
      }
    }

    void cfg1_out::do_sub_siblings(std::vector< toppers::xml::container::object* > objects, int siblings) const
    {
        for ( std::vector< toppers::xml::container::object* >::iterator pObj = objects.begin() ;
            pObj != objects.end();
            ++pObj )
        {
            int SubcontinersSiblings = (*pObj)->getSubcontainers()->size();
            if( SubcontinersSiblings != 0)
            {
                do_sub_siblings( *(*pObj)->getSubcontainers(), SubcontinersSiblings );
            }
            (*pObj)->setSiblings(siblings);
        }
    }

    cfg1_out::xml_obj_map cfg1_out::do_merge(std::vector< toppers::xml::container::object* > objects,
      std::map<std::string, toppers::xml::info> const& info_map ) const
    {
      xml_obj_map result; // ����ƥʤ�Ϣ������

      for ( std::vector< toppers::xml::container::object* >::iterator pModule = objects.begin() ;
          pModule != objects.end();
          ++pModule )
      {
        for ( std::vector< toppers::xml::container::object* >::iterator pObj = (*pModule)->getSubcontainers()->begin() ;
            pObj != (*pModule)->getSubcontainers()->end();
            ++pObj )
        {
          {
            string str = replase_xml_pathname(pObj, info_map);
            result[ str ].push_back( *pObj );
          }
        }
        // ���֥���ƥʤ�Ϣ���������Ͽ
        for ( std::vector< toppers::xml::container::object* >::iterator pObj = (*pModule)->getSubcontainers()->begin() ;
              pObj != (*pModule)->getSubcontainers()->end();
              ++pObj )
        {
          if( (*pObj)->getSubcontainers()->size() != 0)
          {
            do_sub_merge( *(*pObj)->getSubcontainers(), result, info_map);
          }
        }
      }

      // ID�ֹ�γ��դ�
      assign_id(result);

      // ���拾��ƥʤο������
      int SiblingsNumber = 0;
      for ( std::map< std::string, std::vector<toppers::xml::container::object*> >::iterator pObj = result.begin() ;
          pObj != result.end();
          ++pObj )
      {
        SiblingsNumber = pObj->second.size();
        for ( std::vector< toppers::xml::container::object* >::iterator p = pObj->second.begin() ;
            p != pObj->second.end();
            ++p )
        {
          // ���֥���ƥʤη��拾��ƥʿ������
          int SubcontinersSiblings = (*p)->getSubcontainers()->size();
          if( SubcontinersSiblings != 0)
          {
            do_sub_siblings( *(*p)->getSubcontainers(), SubcontinersSiblings );
          }
          (*p)->setSiblings(SiblingsNumber);
        }
      }

      return result;
    }

    /*
     * ����ƥʡ��ѥ�᡼��URI̾��api-table�ǵ��Ҥ���̾�Τ��֤�������
     */
    string cfg1_out::replase_xml_pathname(std::vector< toppers::xml::container::object* >::iterator pObj, 
      std::map<std::string, toppers::xml::info> const& info_map ) const
    {
      string ObjName = (*pObj)->getDefName();
      std::map<std::string, toppers::xml::info>::const_iterator pInfo = info_map.find( ObjName );
      if(pInfo != info_map.end())
      {
        ObjName = Replace(ObjName, pInfo->first, pInfo->second.tfname);
        (*pObj)->setDefName( ObjName );
      }

      for( std::vector< toppers::xml::container::parameter* >::iterator pPara = (*pObj)->getParams()->begin() ;
        pPara != (*pObj)->getParams()->end(); ++pPara)
      {
        string ParamName = (*pPara)->getDefName();
        pInfo = info_map.find( ParamName );
        if(pInfo != info_map.end())
        {
          (*pPara)->setDefName( Replace(ParamName, pInfo->first, pInfo->second.tfname) );
        }
      }
      return ObjName;
    }

    /*!
     *  \brief  ��ȥ륨��ǥ����󤫤ɤ�����Ƚ��
     *  \retval     true  ��ȥ륨��ǥ�����
     *  \retval     false �ӥå�����ǥ�����
     *  \attention  load_srec �ƤӽФ�������������̤������ʤ���
     */
    bool cfg1_out::is_little_endian() const
    {
      return pimpl_->little_endian_;
    }

    /*!
     *  \brief  ��ŪAPI�Υѥ�᡼����S�쥳���ɤ�����������ͤ���������
     */
    void cfg1_out::implementation::do_assign_params()
    {
    }

    void cfg1_out::del_containers()
    {
      for ( std::vector< toppers::xml::container::object* >::iterator pObj = pimpl_->container_array_.begin() ;
        pObj != pimpl_->container_array_.end();
        ++pObj )
      {
        SAX2Handlers::obj_delete((*pObj));
        delete *pObj;
      }
    }
  }
}
