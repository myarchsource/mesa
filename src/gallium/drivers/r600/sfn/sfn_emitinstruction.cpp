/* -*- mesa-c++  -*-
 *
 * Copyright (c) 2019 Collabora LTD
 *
 * Author: Gert Wollny <gert.wollny@collabora.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * on the rights to use, copy, modify, merge, publish, distribute, sub
 * license, and/or sell copies of the Software, and to permit persons to whom
 * the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the next
 * paragraph) shall be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. IN NO EVENT SHALL
 * THE AUTHOR(S) AND/OR THEIR SUPPLIERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
 * OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE
 * USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include "sfn_emitinstruction.h"

#include "sfn_shader_base.h"

namespace r600 {

EmitInstruction::EmitInstruction(ShaderFromNirProcessor& processor):
   m_proc(processor)
{

}

EmitInstruction::~EmitInstruction()
{
}

bool EmitInstruction::emit(nir_instr* instr)
{
   return do_emit(instr);
}

PValue EmitInstruction::from_nir(const nir_src& v, unsigned component, unsigned swizzled)
{
   return m_proc.from_nir(v, component, swizzled);
}

PValue EmitInstruction::from_nir(const nir_alu_src& v, unsigned component)
{
   return m_proc.from_nir(v, component);
}

PValue EmitInstruction::from_nir(const nir_tex_src& v, unsigned component)
{
   return m_proc.from_nir(v, component);
}

PValue EmitInstruction::from_nir(const nir_alu_dest& v, unsigned component)
{
   return m_proc.from_nir(v, component);
}

PValue EmitInstruction::from_nir(const nir_dest& v, unsigned component)
{
   return m_proc.from_nir(v, component);
}

PValue EmitInstruction::from_nir(const nir_src& v, unsigned component)
{
   return m_proc.from_nir(v, component);
}

void EmitInstruction::emit_instruction(Instruction *ir)
{
   return m_proc.emit_instruction(ir);
}

bool EmitInstruction::emit_instruction(EAluOp opcode, PValue dest,
                                       std::vector<PValue> src0,
                                       const std::set<AluModifiers>& m_flags)
{
   return m_proc.emit_instruction(opcode, dest,src0, m_flags);
}

const nir_variable *
EmitInstruction::get_deref_location(const nir_src& v) const
{
   return m_proc.get_deref_location(v);
}

PValue EmitInstruction::from_nir_with_fetch_constant(const nir_src& src, unsigned component)
{
   return m_proc.from_nir_with_fetch_constant(src, component);
}

GPRVector *EmitInstruction::vec_from_nir_with_fetch_constant(const nir_src& src, unsigned mask,
                                            const GPRVector::Swizzle& swizzle)
{
   return m_proc.vec_from_nir_with_fetch_constant(src, mask, swizzle);
}

void EmitInstruction::load_uniform(const nir_alu_src& src)
{
   m_proc.load_uniform(src);
}

int EmitInstruction::lookup_register_index(const nir_src& src) const
{
   return m_proc.lookup_register_index(src);
}

int EmitInstruction::allocate_temp_register()
{
   return m_proc.allocate_temp_register();
}

int EmitInstruction::lookup_register_index(const nir_dest& dst)
{
   return m_proc.lookup_register_index(dst);
}

const nir_load_const_instr*
EmitInstruction::get_literal_register(const nir_src& src) const
{
   if (src.is_ssa)
      return m_proc.get_literal_constant(src.ssa->index);
   else
      return nullptr;
}

PValue EmitInstruction::get_temp_register()
{
   return m_proc.get_temp_register();
}

GPRVector EmitInstruction::get_temp_vec4()
{
   return m_proc.get_temp_vec4();
}

PValue EmitInstruction::create_register_from_nir_src(const nir_src& src, unsigned swizzle)
{
   return m_proc.create_register_from_nir_src(src, swizzle);
}

const std::set<AluModifiers> EmitInstruction::empty = {};
const std::set<AluModifiers> EmitInstruction::write = {alu_write};
const std::set<AluModifiers> EmitInstruction::last_write = {alu_write, alu_last_instr};
const std::set<AluModifiers> EmitInstruction::last = {alu_last_instr};

}

