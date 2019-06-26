


#ifndef TNR_TNRVISITOR_H
#define TNR_TNRVISITOR_H


#include "TNRDSLBaseVisitor.h"
#include "ObjectBuilder.h"

class TnrVisitor : public TNRDSLBaseVisitor
{
public:
    explicit TnrVisitor(ObjectBuilder & objectBuilder) : TNRDSLBaseVisitor(),
                                                            dbg(false), m_indent(0),
                                                            m_objectBuilder(objectBuilder) { };

public:
    //! Return a string that indents by number of spaces times 4
    std::string printIndent() { return std::string(m_indent * 4, ' '); };
    //! Increase indentation
    void indent() { m_indent++; };
    //! Decrease indentation
    void unindent() { if (m_indent > 0) { m_indent--; } }

    antlrcpp::Any visitNew_type_name(TNRDSLParser::New_type_nameContext *ctx) override {
        if (dbg) std::cout << printIndent() << __FUNCTION__ << " " << ctx->getText() << std::endl;
        m_objectBuilder.StartNewType(ctx->getText());   // Reset and save the type name
        return visitChildren(ctx);
    }

    antlrcpp::Any visitDefine_end(TNRDSLParser::Define_endContext *ctx) override {
        if (dbg) std::cout << printIndent() << __FUNCTION__ << " " << ctx->getText() << std::endl << std::endl;
        m_objectBuilder.AddNewType();   // Defining the type is complete
        return visitChildren(ctx);
    }

    antlrcpp::Any visitObject_description(TNRDSLParser::Object_descriptionContext *ctx) override {
        if (dbg) std::cout << printIndent() << __FUNCTION__ << " " << ctx->getText() << std::endl;
        m_objectBuilder.SetDescriptionOnTopOfStack(ctx->getText());
        return visitChildren(ctx);
    }

    antlrcpp::Any visitFormat_string(TNRDSLParser::Format_stringContext *ctx) override {
        m_objectBuilder.SetFormatOnTopOfStack(ctx->getText());
        return visitChildren(ctx);
    }

    antlrcpp::Any visitNewlineon(TNRDSLParser::NewlineonContext *ctx) override {
        m_objectBuilder.SetNewlineOnTopOfStack(true);
        return visitChildren(ctx);
    }

    antlrcpp::Any visitNewlineoff(TNRDSLParser::NewlineoffContext *ctx) override {
        m_objectBuilder.SetNewlineOnTopOfStack(false);
        return visitChildren(ctx);
    }

    antlrcpp::Any visitDescriptionon(TNRDSLParser::DescriptiononContext *ctx) override {
        m_objectBuilder.SetPrintDescriptionOnTopOfStack(true);
        return visitChildren(ctx);
    }

    antlrcpp::Any visitDescriptionoff(TNRDSLParser::DescriptionoffContext *ctx) override {
        m_objectBuilder.SetPrintDescriptionOnTopOfStack(false);
        return visitChildren(ctx);
    }


    antlrcpp::Any visitCompound_start(TNRDSLParser::Compound_startContext *ctx) override {
        indent();
        if (dbg) std::cout << printIndent() << __FUNCTION__ << std::endl;
        m_objectBuilder.PushEmptyCompoundObject();
        return visitChildren(ctx);
    }

    antlrcpp::Any visitCompound_end(TNRDSLParser::Compound_endContext *ctx) override {
        if (dbg) std::cout << printIndent() << __FUNCTION__ << std::endl;
        unindent();
        m_objectBuilder.unindent();
        return visitChildren(ctx);
    }

    antlrcpp::Any visitExisting_type(TNRDSLParser::Existing_typeContext *ctx) override {
        if (dbg) std::cout << printIndent() << __FUNCTION__ << " " << ctx->getText() << std::endl;
        m_objectBuilder.PushEmptyExistingType(ctx->getText());
        return visitChildren(ctx);
    }

    antlrcpp::Any visitCompound_member_end(TNRDSLParser::Compound_member_endContext *ctx) override {
        if (dbg) std::cout << printIndent() << __FUNCTION__ << " Add to parent" << std::endl;
        m_objectBuilder.PopObjectToParentObject();
        return visitChildren(ctx);
    }

    antlrcpp::Any visitFixed_array_type(TNRDSLParser::Fixed_array_typeContext *ctx) override {
        if (dbg) std::cout << printIndent() << __FUNCTION__ << std::endl;
        m_objectBuilder.PushEmptyFixedArray();
        return visitChildren(ctx);
    }

    virtual antlrcpp::Any visitFixed_array_count(TNRDSLParser::Fixed_array_countContext *ctx) override {
        if (dbg) std::cout << printIndent() << __FUNCTION__ << " " << ctx->getText() << std::endl;
        try
        {
            m_objectBuilder.SetFixedArrayLength(std::stoi(ctx->getText()));
        }
        catch (const std::invalid_argument& ia)
        {
            std::cerr << "Invalid argument: " << ia.what() << '\n';
        }

        return visitChildren(ctx);
    }

    antlrcpp::Any visitFixed_array_element_end(TNRDSLParser::Fixed_array_element_endContext *ctx) override {
        if (dbg) std::cout << printIndent() << __FUNCTION__ << std::endl;
        m_objectBuilder.PopElementToFixedArray();
        return visitChildren(ctx);
    }

    antlrcpp::Any visitCounted_array_type(TNRDSLParser::Counted_array_typeContext *ctx) override {
        if (dbg) std::cout << printIndent() << __FUNCTION__ << std::endl;
        m_objectBuilder.PushEmptyCountedArray();
        return visitChildren(ctx);
    }

    antlrcpp::Any visitCounted_array_element_end(TNRDSLParser::Counted_array_element_endContext *ctx) override {
        if (dbg) std::cout << printIndent() << __FUNCTION__ << std::endl;
        m_objectBuilder.PopCounterAndElementToCountedArray();
        return visitChildren(ctx);
    }


private:
    bool dbg;
    uint32_t m_indent;
    ObjectBuilder & m_objectBuilder;
};


#endif //TNR_TNRVISITOR_H
