/**
 * @file BitField_DMA.h
 * @author adem alnajjar (adem.marangoz95@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2023-01-26
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef BIT_FEILD_DMA_H_
#define BIT_FEILD_DMA_H_


/*******************  Bit definition for DMA_CCR register  ********************/
#define DMA_CCR_EN_Pos                      (0U)
#define DMA_CCR_EN_Msk                      (0x1UL << DMA_CCR_EN_Pos)           /*!< 0x00000001 */
#define DMA_CCR_EN                          DMA_CCR_EN_Msk 
#define DMA_CCR_TCIE_Pos                    (1U)
#define DMA_CCR_TCIE_Msk                    (0x1UL << DMA_CCR_TCIE_Pos)         /*!< 0x00000002 */
#define DMA_CCR_TCIE                        DMA_CCR_TCIE_Msk 
#define DMA_CCR_HTIE_Pos                    (2U)
#define DMA_CCR_HTIE_Msk                    (0x1UL << DMA_CCR_HTIE_Pos)         /*!< 0x00000004 */
#define DMA_CCR_HTIE                        DMA_CCR_HTIE_Msk 
#define DMA_CCR_TEIE_Pos                    (3U)
#define DMA_CCR_TEIE_Msk                    (0x1UL << DMA_CCR_TEIE_Pos)         /*!< 0x00000008 */
#define DMA_CCR_TEIE                        DMA_CCR_TEIE_Msk 
#define DMA_CCR_DIR_Pos                     (4U)
#define DMA_CCR_DIR_Msk                     (0x1UL << DMA_CCR_DIR_Pos)          /*!< 0x00000010 */
#define DMA_CCR_DIR                         DMA_CCR_DIR_Msk 
#define DMA_CCR_CIRC_Pos                    (5U)
#define DMA_CCR_CIRC_Msk                    (0x1UL << DMA_CCR_CIRC_Pos)         /*!< 0x00000020 */
#define DMA_CCR_CIRC                        DMA_CCR_CIRC_Msk 
#define DMA_CCR_PINC_Pos                    (6U)
#define DMA_CCR_PINC_Msk                    (0x1UL << DMA_CCR_PINC_Pos)         /*!< 0x00000040 */
#define DMA_CCR_PINC                        DMA_CCR_PINC_Msk 
#define DMA_CCR_MINC_Pos                    (7U)
#define DMA_CCR_MINC_Msk                    (0x1UL << DMA_CCR_MINC_Pos)         /*!< 0x00000080 */
#define DMA_CCR_MINC                        DMA_CCR_MINC_Msk 
#define DMA_CCR_PSIZE_Pos                   (8U)
#define DMA_CCR_PSIZE_Msk                   (0x3UL << DMA_CCR_PSIZE_Pos)        /*!< 0x00000100 */
#define DMA_CCR_PSIZE                       DMA_CCR_PSIZE_Msk 
#define DMA_CCR_MSIZE_Pos                   (10U)
#define DMA_CCR_MSIZE_Msk                   (0x3UL << DMA_CCR_MSIZE_Pos)        /*!< 0x00000001 */
#define DMA_CCR_MSIZE                       DMA_CCR_MSIZE_Msk 
#define DMA_CCR_PL_Pos                      (12U)
#define DMA_CCR_PL_Msk                      (0x3UL << DMA_CCR_PL_Pos)           /*!< 0x00000001 */
#define DMA_CCR_PL                          DMA_CCR_PL_Msk 
#define DMA_CCR_MEM2MEM_Pos                 (14U)
#define DMA_CCR_MEM2MEM_Msk                 (0x1UL << DMA_CCR_MEM2MEM_Pos)      /*!< 0x00000001 */
#define DMA_CCR_MEM2MEM                     DMA_CCR_MEM2MEM_Msk 

/******************************************************************************/



#endif