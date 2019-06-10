


#ifndef TNR_TNRVISITOR_H
#define TNR_TNRVISITOR_H


#include "TNRDSLBaseVisitor.h"

class TnrVisitor : public TNRDSLBaseVisitor
{
public:
    TnrVisitor() = default;
public:
    //! Return a string that indents by number of spaces times 4
    std::string printIndent() { return std::string(m_indent * 4, ' '); };
    //! Increase indentation
    void indent() { m_indent++; };
    //! Decrease indentation
    void unindent() { if (m_indent > 0) { m_indent--; } }

    virtual antlrcpp::Any visitNew_type_name(TNRDSLParser::New_type_nameContext *context) override {
        std::cout << printIndent() << __FUNCTION__ << " " << context->getText() << std::endl;
        return visitChildren(context);
    }

    virtual antlrcpp::Any visitCompound_start(TNRDSLParser::Compound_startContext *context) override {
        indent();
        std::cout << printIndent() << __FUNCTION__ << std::endl;
        return visitChildren(context);
    }

    virtual antlrcpp::Any visitCompound_end(TNRDSLParser::Compound_endContext *context) override {
        unindent();
        std::cout << printIndent() << __FUNCTION__ << std::endl;
        return visitChildren(context);
    }

    virtual antlrcpp::Any visitExisting_type(TNRDSLParser::Existing_typeContext *context) override {
        std::cout << printIndent() << __FUNCTION__ << " " << context->getText() << std::endl;
        return visitChildren(context);
    }

    virtual antlrcpp::Any visitFixed_array(TNRDSLParser::Fixed_arrayContext *context) override {
        std::cout << printIndent() << __FUNCTION__ << " " << context->getText() << std::endl;
        return visitChildren(context);
    }

    virtual antlrcpp::Any visitFixed_array_count(TNRDSLParser::Fixed_array_countContext *context) override {
        std::cout << printIndent() << __FUNCTION__ << " " << context->getText() << std::endl;
        return visitChildren(context);
    }

    virtual antlrcpp::Any visitCounted_array(TNRDSLParser::Counted_arrayContext *context) override {
        std::cout << printIndent() << __FUNCTION__ << " " << context->getText() << std::endl;
        return visitChildren(context);
    }

    virtual antlrcpp::Any visitVariant(TNRDSLParser::VariantContext *context) override {
        std::cout << printIndent() << __FUNCTION__ << " " << context->getText() << std::endl;
        return visitChildren(context);
    }

    virtual antlrcpp::Any visitObject_description(TNRDSLParser::Object_descriptionContext *context) override {
        std::cout << printIndent() << __FUNCTION__ << " " << context->getText() << std::endl;
        return visitChildren(context);
    }
    virtual antlrcpp::Any visitFormat_string(TNRDSLParser::Format_stringContext *context) override {
        std::cout << printIndent() << __FUNCTION__ << " " << context->getText() << std::endl;
        return visitChildren(context);
    }

//    virtual antlrcpp::Any visitOptional_parameters(TNRDSLParser::Optional_parametersContext *context) override {
//        std::cout << printIndent() << __FUNCTION__ << " " << context->getText() << std::endl;
//        return visitChildren(context);
//    }

    virtual antlrcpp::Any visitNewlineon(TNRDSLParser::NewlineonContext *context) override {
        std::cout << printIndent() << __FUNCTION__ << " " << context->getText() << std::endl;
        return visitChildren(context);
    }

    virtual antlrcpp::Any visitNewlineoff(TNRDSLParser::NewlineoffContext *context) override {
        std::cout << printIndent() << __FUNCTION__ << " " << context->getText() << std::endl;
        return visitChildren(context);
    }

    virtual antlrcpp::Any visitDescriptionon(TNRDSLParser::DescriptiononContext *context) override {
        std::cout << printIndent() << __FUNCTION__ << " " << context->getText() << std::endl;
        return visitChildren(context);
    }

    virtual antlrcpp::Any visitDescriptionoff(TNRDSLParser::DescriptionoffContext *context) override {
        std::cout << printIndent() << __FUNCTION__ << " " << context->getText() << std::endl;
        return visitChildren(context);
    }

//    virtual antlrcpp::Any visitObject_name_parameter(TNRDSLParser::Object_name_parameterContext *context) override {
//        std::cout << printIndent() << __FUNCTION__ << " " << context->getText() << std::endl;
//        return visitChildren(context);
//    }
//
//    virtual antlrcpp::Any visitFormat_parameter(TNRDSLParser::Format_parameterContext *context) override {
//        std::cout << printIndent() << __FUNCTION__ << " " << context->getText() << std::endl;
//        return visitChildren(context);
//    }

//    virtual antlrcpp::Any visitDescription_on(TNRDSLParser::Description_onContext *context) override {
//        std::cout << printIndent() << __FUNCTION__ << " " << context->getText() << std::endl;
//        return visitChildren(context);
//    }
//
//    virtual antlrcpp::Any visitDescription_off(TNRDSLParser::Description_offContext *context) override {
//        std::cout << printIndent() << __FUNCTION__ << " " << context->getText() << std::endl;
//        return visitChildren(context);
//    }

//    virtual antlrcpp::Any visitNewline_on(TNRDSLParser::Newline_onContext *context) override {
//        std::cout << printIndent() << __FUNCTION__ << " " << context->getText() << std::endl;
//        return visitChildren(context);
//    }
//
//    virtual antlrcpp::Any visitNewline_off(TNRDSLParser::Newline_offContext *context) override {
//        std::cout << printIndent() << __FUNCTION__ << " " << context->getText() << std::endl;
//        return visitChildren(context);
//    }

private:
    uint32_t m_indent;
};


#endif //TNR_TNRVISITOR_H
