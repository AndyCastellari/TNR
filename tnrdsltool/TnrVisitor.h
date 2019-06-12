


#ifndef TNR_TNRVISITOR_H
#define TNR_TNRVISITOR_H


#include "TNRDSLBaseVisitor.h"
#include "ObjectBuilder.h"

class TnrVisitor : public TNRDSLBaseVisitor
{
public:
    explicit TnrVisitor(ObjectBuilder & objectBuilder) : TNRDSLBaseVisitor(), m_indent(0), m_objectBuilder(objectBuilder) { };

public:
    //! Return a string that indents by number of spaces times 4
    std::string printIndent() { return std::string(m_indent * 4, ' '); };
    //! Increase indentation
    void indent() { m_indent++; };
    //! Decrease indentation
    void unindent() { if (m_indent > 0) { m_indent--; } }

    antlrcpp::Any visitNew_type_name(TNRDSLParser::New_type_nameContext *context) override {
        std::cout << printIndent() << __FUNCTION__ << " " << context->getText() << std::endl;
        return visitChildren(context);
    }

    antlrcpp::Any visitDefine_end(TNRDSLParser::Define_endContext *context) override {
        std::cout << printIndent() << __FUNCTION__ << " " << context->getText() << std::endl << std::endl;
        return visitChildren(context);
    }

    antlrcpp::Any visitCompound_start(TNRDSLParser::Compound_startContext *context) override {
        indent();
        std::cout << printIndent() << __FUNCTION__ << std::endl;
        return visitChildren(context);
    }

    antlrcpp::Any visitCompound_end(TNRDSLParser::Compound_endContext *context) override {
        std::cout << printIndent() << __FUNCTION__ << std::endl;
        unindent();
        return visitChildren(context);
    }

    antlrcpp::Any visitExisting_type(TNRDSLParser::Existing_typeContext *context) override {
        std::cout << printIndent() << __FUNCTION__ << " " << context->getText() << std::endl;
        return visitChildren(context);
    }

    antlrcpp::Any visitFixed_array(TNRDSLParser::Fixed_arrayContext *context) override {
        std::cout << printIndent() << __FUNCTION__ << " " << context->getText() << std::endl;
        return visitChildren(context);
    }

    antlrcpp::Any visitFixed_array_count(TNRDSLParser::Fixed_array_countContext *context) override {
        std::cout << printIndent() << __FUNCTION__ << " " << context->getText() << std::endl;
        return visitChildren(context);
    }

    antlrcpp::Any visitCounted_array(TNRDSLParser::Counted_arrayContext *context) override {
        std::cout << printIndent() << __FUNCTION__ << " " << context->getText() << std::endl;
        return visitChildren(context);
    }

    antlrcpp::Any visitVariant(TNRDSLParser::VariantContext *context) override {
        std::cout << printIndent() << __FUNCTION__ << " " << context->getText() << std::endl;
        return visitChildren(context);
    }

    antlrcpp::Any visitObject_description(TNRDSLParser::Object_descriptionContext *context) override {
        std::cout << printIndent() << __FUNCTION__ << " " << context->getText() << std::endl;
        return visitChildren(context);
    }
    antlrcpp::Any visitFormat_string(TNRDSLParser::Format_stringContext *context) override {
        std::cout << printIndent() << __FUNCTION__ << " " << context->getText() << std::endl;
        return visitChildren(context);
    }

//    virtual antlrcpp::Any visitOptional_parameters(TNRDSLParser::Optional_parametersContext *context) override {
//        std::cout << printIndent() << __FUNCTION__ << " " << context->getText() << std::endl;
//        return visitChildren(context);
//    }

    antlrcpp::Any visitNewlineon(TNRDSLParser::NewlineonContext *context) override {
        std::cout << printIndent() << __FUNCTION__ << " " << context->getText() << std::endl;
        return visitChildren(context);
    }

    antlrcpp::Any visitNewlineoff(TNRDSLParser::NewlineoffContext *context) override {
        std::cout << printIndent() << __FUNCTION__ << " " << context->getText() << std::endl;
        return visitChildren(context);
    }

    antlrcpp::Any visitDescriptionon(TNRDSLParser::DescriptiononContext *context) override {
        std::cout << printIndent() << __FUNCTION__ << " " << context->getText() << std::endl;
        return visitChildren(context);
    }

    antlrcpp::Any visitDescriptionoff(TNRDSLParser::DescriptionoffContext *context) override {
        std::cout << printIndent() << __FUNCTION__ << " " << context->getText() << std::endl;
        return visitChildren(context);
    }

    antlrcpp::Any visitSimple_start(TNRDSLParser::Simple_startContext *ctx) override {
        std::cout << printIndent() << __FUNCTION__ << " " << ctx->getText() << std::endl;
        return visitChildren(ctx);
    }

    antlrcpp::Any visitSimple_end(TNRDSLParser::Simple_endContext *ctx) override {
        std::cout << printIndent() << __FUNCTION__ << " " << ctx->getText() << std::endl;
        return visitChildren(ctx);
    }



private:
    uint32_t m_indent;
    ObjectBuilder & m_objectBuilder;
};


#endif //TNR_TNRVISITOR_H
