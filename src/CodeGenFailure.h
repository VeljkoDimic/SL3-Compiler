#ifndef CODEGEN_FAILURE_H
#define CODEGEN_FAILURE_H

// CodeGen failure class
class CodeGenFailure {
    private:
        std::string message;
    public:
        CodeGenFailure(std::string message);

        std::string getMessage() const;
};

#endif
