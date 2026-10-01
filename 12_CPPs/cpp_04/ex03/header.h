/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolotar <mzolotar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 20:29:25 by mzolotar          #+#    #+#             */
/*   Updated: 2025/10/27 12:32:06 by mzolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
#define HEADER_H

// ====================== AMateria ======================
#define AMAT_DEF_CTOR	"[C] AMateria Default Constructor called"
#define AMAT_ARG_CTOR	"[C] AMateria Attribute Constructor called"
#define AMAT_COPY_CTOR	"[C] AMateria Copy Constructor called"
#define AMAT_DTOR		"[D] AMateria Destructor called"
#define AMAT_ASS_OP		"[O] AMateria Assignment Operator called"

// ====================== Ice ==========================
#define ICE_DEF_CTOR	"[C] Ice Default Constructor called"
#define ICE_COPY_CTOR	"[C] Ice Copy Constructor called"
#define ICE_DTOR		"[D] Ice Destructor called"
#define ICE_ASS_OP		"[O] Ice Assignment Operator called"
#define ICE_MSG			"* shoots an ice bolt at "
#define ICE_END			" *"

// ====================== Cure =========================
#define CURE_DEF_CTOR	"[C] Cure Default Constructor called"
#define CURE_COPY_CTOR	"[C] Cure Copy Constructor called"
#define CURE_DTOR		"[D] Cure Destructor called"
#define CURE_ASS_OP		"[O] Cure Assignment Operator called"
#define CURE_MSG		"* heals "
#define CURE_END		"'s wounds *"

// ====================== ICharacter ====================
#define ICHAR_DTOR		"[D] ICharacter Destructor called"

// ====================== Character =====================
#define CHAR_DEF_CTOR	"[C] Character Default Constructor called"
#define CHAR_ARG_CTOR	"[C] Character Attribute Constructor called"
#define CHAR_COPY_CTOR	"[C] Character Copy Constructor called"
#define CHAR_DTOR		"[D] Character Destructor called"
#define CHAR_ASS_OP		"[O] Character Assignment Operator called"

// ====================== IMateriaSource ================
#define IMSRC_DTOR		"[D] IMateriaSource Destructor called"

// ====================== MateriaSource ==================
#define MSRC_DEF_CTOR	"[C] MateriaSource Default Constructor called"
#define MSRC_COPY_CTOR	"[C] MateriaSource Copy Constructor called"
#define MSRC_DTOR		"[D] MateriaSource Destructor called"
#define MSRC_ASS_OP		"[O] MateriaSource Assignment Operator called"
#define MSRC_FULL		"[E] MateriaSource inventory full, cannot learn more Materias"
#define MSRC_CREAT		"MateriaSource created a Materia of type "
#define MSRC_UNKNOWN	"[E] MateriaSource doesn't know this type: "
#define MSRC_NULL		"[E] MateriaSource cannot learn a NULL or invalid Materia."

#endif
