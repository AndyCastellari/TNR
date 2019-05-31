


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

    virtual antlrcpp::Any visitNew_type_name(TNRDSLParser::New_type_nameContext *ctx) override {
        std::cout << printIndent() << __FUNCTION__ << " " << ctx->getText() << std::endl;
        return visitChildren(ctx);
    }

    virtual antlrcpp::Any visitCompound_start(TNRDSLParser::Compound_startContext *ctx) override {
        indent();
        std::cout << printIndent() << __FUNCTION__ << std::endl;
        return visitChildren(ctx);
    }

    virtual antlrcpp::Any visitCompound_end(TNRDSLParser::Compound_endContext *ctx) override {
        unindent();
        std::cout << printIndent() << __FUNCTION__ << std::endl;
        return visitChildren(ctx);
    }

    virtual antlrcpp::Any visitExisting_type(TNRDSLParser::Existing_typeContext *ctx) override {
        std::cout << printIndent() << __FUNCTION__ << " " << ctx->getText() << std::endl;
        return visitChildren(ctx);
    }

    virtual antlrcpp::Any visitFixed_array(TNRDSLParser::Fixed_arrayContext *ctx) override {
        std::cout << printIndent() << __FUNCTION__ << " " << ctx->getText() << std::endl;
        return visitChildren(ctx);
    }

    virtual antlrcpp::Any visitFixed_array_count(TNRDSLParser::Fixed_array_countContext *ctx) override {
        std::cout << printIndent() << __FUNCTION__ << " " << ctx->getText() << std::endl;
        return visitChildren(ctx);
    }

    virtual antlrcpp::Any visitCounted_array(TNRDSLParser::Counted_arrayContext *ctx) override {
        std::cout << printIndent() << __FUNCTION__ << " " << ctx->getText() << std::endl;
        return visitChildren(ctx);
    }

    virtual antlrcpp::Any visitVariant(TNRDSLParser::VariantContext *ctx) override {
        std::cout << printIndent() << __FUNCTION__ << " " << ctx->getText() << std::endl;
        return visitChildren(ctx);
    }

    virtual antlrcpp::Any visitOptional_parameters(TNRDSLParser::Optional_parametersContext *ctx) override {
        std::cout << printIndent() << __FUNCTION__ << " " << ctx->getText() << std::endl;
        return visitChildren(ctx);
    }
//    virtual antlrcpp::Any visitObject_name_parameter(TNRDSLParser::Object_name_parameterContext *ctx) override {
//        std::cout << printIndent() << __FUNCTION__ << " " << ctx->getText() << std::endl;
//        return visitChildren(ctx);
//    }
//
//    virtual antlrcpp::Any visitFormat_parameter(TNRDSLParser::Format_parameterContext *ctx) override {
//        std::cout << printIndent() << __FUNCTION__ << " " << ctx->getText() << std::endl;
//        return visitChildren(ctx);
//    }

//    virtual antlrcpp::Any visitDescription_on(TNRDSLParser::Description_onContext *ctx) override {
//        std::cout << printIndent() << __FUNCTION__ << " " << ctx->getText() << std::endl;
//        return visitChildren(ctx);
//    }
//
//    virtual antlrcpp::Any visitDescription_off(TNRDSLParser::Description_offContext *ctx) override {
//        std::cout << printIndent() << __FUNCTION__ << " " << ctx->getText() << std::endl;
//        return visitChildren(ctx);
//    }

//    virtual antlrcpp::Any visitNewline_on(TNRDSLParser::Newline_onContext *ctx) override {
//        std::cout << printIndent() << __FUNCTION__ << " " << ctx->getText() << std::endl;
//        return visitChildren(ctx);
//    }
//
//    virtual antlrcpp::Any visitNewline_off(TNRDSLParser::Newline_offContext *ctx) override {
//        std::cout << printIndent() << __FUNCTION__ << " " << ctx->getText() << std::endl;
//        return visitChildren(ctx);
//    }

private:
    uint32_t m_indent;
};


#endif //TNR_TNRVISITOR_H
