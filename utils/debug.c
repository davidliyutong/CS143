//
// Created by 厉宇桐 on 2020/12/1.
//
// Code that displays debug information

#include "debug.h"

void disp_annalex_res(char *psReadBuffer, lac_queue_t *pqueRes) {
    /* This function displays the analex result */
    printf("---- Annalex result ----\n");
    queue_node_t *tmp = pqueRes->pFront;
    lexeme_t res;
    int flag = FALSE;
    if (pqueRes->iLength > 0) {
        while (TRUE) {
            res = *(lexeme_t *) tmp->pData;
            switch (res.type) {
                case WORD: {
                    printf("M(\"%.*s\")->", res.iEnd - res.iStart, psReadBuffer + res.iStart);
                    break;
                }
                case STRING: {
                    printf("S(\"%.*s\")->", res.iEnd - res.iStart, psReadBuffer + res.iStart);
                    break;
                }
                case NUMBER: {
                    printf("N(\"%.*s\")->", res.iEnd - res.iStart, psReadBuffer + res.iStart);
                    break;
                }
                default: {
                    printf("ERR(\"%.*s\")->", res.iEnd - res.iStart, psReadBuffer + res.iStart);
                }

            }
            tmp = tmp->pNext;
            if (flag == TRUE) break;
            if (tmp == tmp->pNext) {
                flag = TRUE;
            }
        }
    }
    printf("\n-------------------------\n\n");
}

void disp_postfix_exp(lac_queue_t *quePostfixExp) {
    /* This function displays the postfix expression */
    printf("--- Postfix expresion ---\n");
    queue_node_t *tmp = quePostfixExp->pFront;
    exp_btnode_t res;
    int flag = FALSE;
    while (TRUE) {
        res = *(exp_btnode_t *) tmp->pData;
        switch (res.type) {
            case CALC_NUMBER: {
                printf("%d ", res.u_Data.iNumber);
                break;
            }
            case CALC_OP_1:
            case CALC_OP_2:
            case CALC_OP_3: {
                printf("%c ", res.u_Data.cOP);
                break;
            }

            default: {
                printf("ERR ");
            }

        }
        tmp = tmp->pNext;
        if (flag == TRUE) break;
        if (tmp == tmp->pNext) {
            flag = TRUE;
        }
    }
    printf("\n-------------------------\n\n");

}

void disp_exp_tree(exp_btnode_t ExpTreeRoot) { // OK to pass the exptree's root by copy: it's small
    /* This function displays the expression tree */
    printf("--------- Tree ----------\n");
    lac_queue_t queTmp;
    queue_init(&queTmp);
    lac_queue_t queDepth;
    queue_init(&queDepth);
    int iDepth = 0;
    int iNewDepth = 0;
    exp_btnode_t TreeNodeTmp;

    queue_push_back(&queTmp, (void *) &ExpTreeRoot, sizeof(exp_btnode_t));   //enque the root node
    queue_push_back(&queDepth, (void *) &iDepth, sizeof(int));


    while (!queue_is_empty(&queTmp))  // if the queue is not empty
    {
        TreeNodeTmp = *((exp_btnode_t *) (queTmp.pFront->pData));
        iNewDepth = *(int *) (queDepth.pFront->pData);

        if (iNewDepth > iDepth) {
            iDepth += 1;
            printf("\n");
        }

        if (TreeNodeTmp.type == CALC_OP_1 || TreeNodeTmp.type == CALC_OP_2 || TreeNodeTmp.type == CALC_OP_3) {
            printf("%c\t", TreeNodeTmp.u_Data.cOP);
        } else {
            printf("%d\t", TreeNodeTmp.u_Data.iNumber);
        }

        iNewDepth += 1;
        if (((exp_btnode_t *) (queTmp.pFront->pData))->lNode != NULL)   //if hase left child，enque left child
        {

            queue_push_back(&queTmp, (void *) (((exp_btnode_t *) (queTmp.pFront->pData))->lNode), sizeof(exp_btnode_t));
            queue_push_back(&queDepth, (void *) &iNewDepth, sizeof(int));
        }
        if (((exp_btnode_t *) (queTmp.pFront->pData))->rNode != NULL)   //if hase left child，enque left child
        {
            queue_push_back(&queTmp, (void *) (((exp_btnode_t *) (queTmp.pFront->pData))->rNode), sizeof(exp_btnode_t));
            queue_push_back(&queDepth, (void *) &iNewDepth, sizeof(int));
        }

        queue_pop_front(&queTmp, NULL); // dequeue the visited data
        queue_pop_front(&queDepth, NULL); // dequeue the visited depth
    }
    printf("\n-------------------------\n\n");
}

void disp_symtable(symtable_t *pSymTable) {
    /* This function displays the symbol table */

    printf("------ Symbol Table -----\n");
    int idx = 1;
    while (TRUE) {
        int iLength = pSymTable->Symbols[idx].i;
        for (int i = 0; i < iLength; i++) {
            printf("%c", pSymTable->Symbols[++idx].c);
        }
        fflush(stdout);
        printf("(%d)", pSymTable->Symbols[idx + 1].i); // CFA
        idx += 3;
        if (idx >= pSymTable->iLength) break;
        printf(" -> ");
    }
    printf("\n-------------------------\n\n");
}

void disp_vmtable(vmtable_t *pVMTable) {
    /* This function displays the VM table */

    printf("-------- VM Table -------\n");
    for (int idx = 0; idx <= pVMTable->iTail; ++idx) {
        printf("%d:%d ", idx, pVMTable->OpCodes[idx]);
        if (idx % 10 == 0 && idx != 0) {
            printf("\n\n");
        }
    }
    fflush(stdout);
    printf("\n-------------------------\n\n");
}

void visualize(char *psReadBuffer, lac_queue_t *pqueRes) {
    printf("\n---- Highlight result ----\n");
    lexeme_t res;
    int printIdx = 0;
//    printf("ddd");
    queue_node_t *tmp = pqueRes->pFront;
    int flag = FALSE;
    while (TRUE) {
        res = *(lexeme_t *) tmp->pData;

        /* print spaces */
        printf("%.*s", res.iStart - printIdx, psReadBuffer + printIdx);
//        printIdx += res.iStart - printIdx;

        /* print item */
        switch (res.type) {
            case WORD:
                printf("\033[%dm%.*s\033[0m", COLOR_WORD, res.iEnd - res.iStart, psReadBuffer + res.iStart);
                break;
            case STRING:
                printf("\033[%dm%.*s\033[0m", COLOR_STRING, res.iEnd - res.iStart, psReadBuffer + res.iStart);
                break;
            case NUMBER:
                printf("\033[%dm%.*s\033[0m", COLOR_NUMBER, res.iEnd - res.iStart, psReadBuffer + res.iStart);
                break;
            default:;
        }
        printIdx = res.iEnd;

        tmp = tmp->pNext;
        if (flag == TRUE) break;
        if (tmp == tmp->pNext) {
            flag = TRUE;
        }
    }
    printf("\n-------------------------\n");
}