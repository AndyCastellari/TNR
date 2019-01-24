


#ifndef TNR_TNRVISITOR_H
#define TNR_TNRVISITOR_H


#include "TNRDSLBaseVisitor.h"

class TnrVisitor : public TNRDSLBaseVisitor
{
public:
    //! Return a string that indents by number of spaces times 4
    std::string indent() { return std::string(m_indent * 4, ' '); };

    virtual antlrcpp::Any visitNew_type_name(TNRDSLParser::New_type_nameContext *ctx) override {
        std::cout << indent() << __FUNCTION__ << " " << ctx->getText() << std::endl;
        return visitChildren(ctx);
    }

    virtual antlrcpp::Any visitCompound_start(TNRDSLParser::Compound_startContext *ctx) override {
        m_indent++;
        std::cout << indent() << __FUNCTION__ << std::endl;
        return visitChildren(ctx);
    }

    virtual antlrcpp::Any visitCompound_end(TNRDSLParser::Compound_endContext *ctx) override {
        if (m_indent > 0)
        {
            m_indent--;
        }
        std::cout << indent() << __FUNCTION__ << std::endl;
        return visitChildren(ctx);
    }

    virtual antlrcpp::Any visitExisting_type(TNRDSLParser::Existing_typeContext *ctx) override {
        std::cout << indent() << __FUNCTION__ << " " << ctx->getText() << std::endl;
        return visitChildren(ctx);
    }

    virtual antlrcpp::Any visitFixed_array(TNRDSLParser::Fixed_arrayContext *ctx) override {
        std::cout << indent() << __FUNCTION__ << " " << ctx->getText() << std::endl;
        return visitChildren(ctx);
    }

    virtual antlrcpp::Any visitFixed_array_count(TNRDSLParser::Fixed_array_countContext *ctx) override {
        std::cout << indent() << __FUNCTION__ << " " << ctx->getText() << std::endl;
        return visitChildren(ctx);
    }

    virtual antlrcpp::Any visitCounted_array(TNRDSLParser::Counted_arrayContext *ctx) override {
        std::cout << indent() << __FUNCTION__ << " " << ctx->getText() << std::endl;
        return visitChildren(ctx);
    }

    virtual antlrcpp::Any visitVariant(TNRDSLParser::VariantContext *ctx) override {
        std::cout << indent() << __FUNCTION__ << " " << ctx->getText() << std::endl;
        return visitChildren(ctx);
    }

private:
    uint32_t m_indent;
};


#endif //TNR_TNRVISITOR_H
