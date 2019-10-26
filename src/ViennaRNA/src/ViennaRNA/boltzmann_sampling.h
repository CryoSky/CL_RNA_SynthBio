#ifndef VIENNA_RNA_PACKAGE_BOLTZMANN_SAMPLING_H
#define VIENNA_RNA_PACKAGE_BOLTZMANN_SAMPLING_H

#include <ViennaRNA/datastructures/basic.h>

/**
 *  @file boltzmann_sampling.h
 *  @ingroup subopt_and_representatives
 *  @brief Boltzmann Sampling of secondary structures from the ensemble
 *
 *  A.k.a. Stochastic backtracking
 */


/**
 *  @addtogroup subopt_stochbt
 *  @{
 *  @brief  Functions to draw random structure samples from the ensemble according to their
 *          equilibrium probability
 */
typedef void (vrna_boltzmann_sampling_callback)(const char  *stucture,
                                                void        *data);


/**
 *  @brief Sample a secondary structure of a subsequence from the Boltzmann ensemble according its probability
 *
 *  @pre    Unique multiloop decomposition has to be active upon creation of @p vc with vrna_fold_compound()
 *          or similar. This can be done easily by passing vrna_fold_compound() a model details parameter
 *          with vrna_md_t.uniq_ML = 1.
 *  @pre    vrna_pf() has to be called first to fill the partition function matrices
 *
 *  @param  vc      The fold compound data structure
 *  @param  length  The length of the subsequence to consider (starting with 5' end)
 *  @return         A sampled secondary structure in dot-bracket notation (or NULL on error)
 */
char *vrna_pbacktrack5(vrna_fold_compound_t *vc,
                       int                  length);


/**
 *  @brief Samples multiple secondary structures non-redundantly from the Boltzmann ensemble according its probability
 *
 *  @ingroup subopt_stochbt
 *  @pre    The fold compound has to be obtained using the #VRNA_OPTION_HYBRID option in vrna_fold_compound()
 *  @pre    vrna_pf() has to be called first to fill the partition function matrices
 *
 *  @note   In some cases, this function does not return the number of requested samples but a smaller number.
 *          This may happen if a) the number of requested structures is larger than the total number of structures
 *          in the ensemble, or b) numeric instabilities prevent the backtracking function to enumerate structures
 *          with very high free energies.
 *
 *  @param  vc        The fold compound data structure
 *  @param  num_samples The number of desired non-redundant samples
 *  @return           A list of sampled secondary structures in dot-bracket notation, terminated by @em NULL
 */
char **vrna_pbacktrack_nr(vrna_fold_compound_t  *vc,
                          int                   num_samples);


void
vrna_pbacktrack_nr_cb(vrna_fold_compound_t              *vc,
                      int                               num_samples,
                      vrna_boltzmann_sampling_callback  *cb,
                      void                              *data);


/**
 *  @brief Sample a secondary structure (consensus structure) from the Boltzmann ensemble according its probability
 *
 *  @pre    Unique multiloop decomposition has to be active upon creation of @p vc with vrna_fold_compound()
 *          or similar. This can be done easily by passing vrna_fold_compound() a model details parameter
 *          with vrna_md_t.uniq_ML = 1.
 *  @pre    vrna_pf() has to be called first to fill the partition function matrices
 *
 *  @note This function is polymorphic. It accepts #vrna_fold_compound_t of type
 *        #VRNA_FC_TYPE_SINGLE, and #VRNA_FC_TYPE_COMPARATIVE.
 *
 *  @note The function will automagically detect cicular RNAs based on the model_details in exp_params as
 *        provided via the #vrna_fold_compound_t
 *
 *  @param  vc      The fold compound data structure
 *  @return         A sampled secondary structure in dot-bracket notation (or NULL on error)
 */
char *vrna_pbacktrack(vrna_fold_compound_t *vc);


/**@}*/


#endif
