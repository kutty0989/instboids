/*
---------------------------------------------------------------------------
Open Asset Import Library (assimp)
---------------------------------------------------------------------------

Copyright (c) 2006-2019, assimp team



All rights reserved.

Redistribution and use of this software in source and binary forms,
with or without modification, are permitted provided that the following
conditions are met:

* Redistributions of source code must retain the above
  copyright notice, this list of conditions and the
  following disclaimer.

* Redistributions in binary form must reproduce the above
  copyright notice, this list of conditions and the
  following disclaimer in the documentation and/or other
  materials provided with the distribution.

* Neither the name of the assimp team, nor the names of its
  contributors may be used to endorse or promote products
  derived from this software without specific prior
  written permission of the assimp team.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
"AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
�S���쌠���L�B

�\�[�X����уo�C�i���`���ł̂��̃\�t�g�E�F�A�̍Ĕz�z����юg�p�A
�ύX�̗L���ɂ�����炸�A���̏����ŋ�����܂��B
��������������Ă���:

* �\�[�X�R�[�h�̍Ĕz�z�͏�L��ێ�����K�v������܂�
  ���쌠�\���A���̏������X�g�����
  �ȉ��̖Ɛӎ����B

* �o�C�i���`���ł̍Ĕz�z�́A��L���Č�����K�v������܂�
  ���쌠�\���A���̏������X�g�����
  �h�L�������g�����/�܂��͂��̑��̎��̖Ɛӎ���
  �z�z���ƂƂ��ɒ񋟂���鎑���B

* assimp�`�[���̖��O�����̖��O������܂���
  ��e�҂́A���i�𐄏��܂��͐�`���邽�߂Ɏg�p�����ꍇ������܂�
  ����̎��O�m�F�Ȃ��ɁA���̃\�t�g�E�F�A����h������
  assimp �`�[���̏��ʂɂ�鋖�B

���̃\�t�g�E�F�A�́A���쌠���L�҂���эv���҂ɂ���Ē񋟂���܂�
�u����̂܂܁v����і����I�܂��َ͖��I�ȕۏ؂��܂݂܂����A�����ł͂���܂���B
���i������ѓK�����َ̖��̕ۏ؂Ɍ��肳��܂��B
����̖ړI�͔۔F����܂��B�����Ȃ�ꍇ���A���쌠��������Ȃ����̂Ƃ��܂�
���L�҂܂��͍v���҂́A���ړI�A�ԐړI�A�t���I�A
���ʑ��Q�A�����I���Q�A���ʓI���Q (�ȉ����܂ނ��A
��֏��i�܂��̓T�[�r�X�̒��B�Ɍ��肳��܂��B�g�p�̑����A
�f�[�^�A�܂��͗��v;�܂��̓r�W�l�X�̒��f) �����̔@�����킸�A
�_��A���i�ӔC�A�܂��͕s�@�s�ׂɂ�����炸�A�ӔC�̗��_
(�ߎ��܂��͂��̑����܂�) �g�p���牽�炩�̌`�Ő�����
���̂悤�ȑ��Q�̉\���ɂ��Ēm�炳��Ă����Ƃ��Ă��A���̃\�t�g�E�F�A��
---------------------------------------------------------------------------
*/

/** 
  * @file   anim.h
  * @brief  Defines the data structures in which the imported animations
  *         are returned.
  */
#pragma once
#ifndef AI_ANIM_H_INC
#define AI_ANIM_H_INC

#include <assimp/types.h>
#include <assimp/quaternion.h>

#ifdef __cplusplus
extern "C" {
#endif

// ---------------------------------------------------------------------------
/** A time-value pair specifying a certain 3D vector for the given time. */
struct aiVectorKey
{
    
/** ���̃L�[�̎��� */
    double mTime;

    /** The value of this key */
    C_STRUCT aiVector3D mValue;

#ifdef __cplusplus

    /// @brief  The default constructor.
    aiVectorKey() AI_NO_EXCEPT
    : mTime( 0.0 )
    , mValue() {
        // empty
    }

    /// @brief  Construction from a given time and key value.

    aiVectorKey(double time, const aiVector3D& value)
    : mTime( time )
    , mValue( value ) {
        // empty
    }

    typedef aiVector3D elem_type;

    // Comparison operators. For use with std::find();
    bool operator == (const aiVectorKey& rhs) const {
        return rhs.mValue == this->mValue;
    }
    bool operator != (const aiVectorKey& rhs ) const {
        return rhs.mValue != this->mValue;
    }

    // Relational operators. For use with std::sort();
    bool operator < (const aiVectorKey& rhs ) const {
        return mTime < rhs.mTime;
    }
    bool operator > (const aiVectorKey& rhs ) const {
        return mTime > rhs.mTime;
    }
#endif // __cplusplus
};

// ---------------------------------------------------------------------------
/** A time-value pair specifying a rotation for the given time.
 *  Rotations are expressed with quaternions. */
struct aiQuatKey
{
    /** The time of this key */
    double mTime;

    /** The value of this key */
    C_STRUCT aiQuaternion mValue;

#ifdef __cplusplus
    aiQuatKey() AI_NO_EXCEPT
    : mTime( 0.0 )
    , mValue() {
        // empty
    }

    /** Construction from a given time and key value */
    aiQuatKey(double time, const aiQuaternion& value)
        :   mTime   (time)
        ,   mValue  (value)
    {}

    typedef aiQuaternion elem_type;

    // Comparison operators. For use with std::find();
    bool operator == (const aiQuatKey& rhs ) const {
        return rhs.mValue == this->mValue;
    }
    bool operator != (const aiQuatKey& rhs ) const {
        return rhs.mValue != this->mValue;
    }

    // Relational operators. For use with std::sort();
    bool operator < (const aiQuatKey& rhs ) const {
        return mTime < rhs.mTime;
    }
    bool operator > (const aiQuatKey& rhs ) const {
        return mTime > rhs.mTime;
    }
#endif
};

// ---------------------------------------------------------------------------
/** Binds a anim-mesh to a specific point in time. */
struct aiMeshKey
{
    /** The time of this key */
    double mTime;

    /** Index into the aiMesh::mAnimMeshes array of the
     *  mesh corresponding to the #aiMeshAnim hosting this
     *  key frame. The referenced anim mesh is evaluated
     *  according to the rules defined in the docs for #aiAnimMesh.*/
    unsigned int mValue;

#ifdef __cplusplus

    aiMeshKey() AI_NO_EXCEPT
    : mTime(0.0)
    , mValue(0)
    {
    }

    /** Construction from a given time and key value */
    aiMeshKey(double time, const unsigned int value)
        :   mTime   (time)
        ,   mValue  (value)
    {}

    typedef unsigned int elem_type;

    // Comparison operators. For use with std::find();
    bool operator == (const aiMeshKey& o) const {
        return o.mValue == this->mValue;
    }
    bool operator != (const aiMeshKey& o) const {
        return o.mValue != this->mValue;
    }

    // Relational operators. For use with std::sort();
    bool operator < (const aiMeshKey& o) const {
        return mTime < o.mTime;
    }
    bool operator > (const aiMeshKey& o) const {
        return mTime > o.mTime;
    }

#endif
};

// ---------------------------------------------------------------------------
/** Binds a morph anim mesh to a specific point in time. */
struct aiMeshMorphKey
{
    /** The time of this key */
    double mTime;

    /** The values and weights at the time of this key */
    unsigned int *mValues;
    double *mWeights;

    /** The number of values and weights */
    unsigned int mNumValuesAndWeights;
#ifdef __cplusplus
	aiMeshMorphKey() AI_NO_EXCEPT
		: mTime(0.0)
		, mValues(nullptr)
		, mWeights(nullptr)
		, mNumValuesAndWeights(0)
	{

	}

    ~aiMeshMorphKey()
    {
        if (mNumValuesAndWeights && mValues && mWeights) {
            delete [] mValues;
            delete [] mWeights;
        }
    }
#endif
};

// ---------------------------------------------------------------------------
/** Defines how an animation channel behaves outside the defined time
 *  range. This corresponds to aiNodeAnim::mPreState and
 *  aiNodeAnim::mPostState.*/
enum aiAnimBehaviour
{
    /** The value from the default node transformation is taken*/
    aiAnimBehaviour_DEFAULT  = 0x0,

    /** The nearest key value is used without interpolation */
    aiAnimBehaviour_CONSTANT = 0x1,

    /** The value of the nearest two keys is linearly
     *  extrapolated for the current time value.*/
    aiAnimBehaviour_LINEAR   = 0x2,

    /** The animation is repeated.
     *
     *  If the animation key go from n to m and the current
     *  time is t, use the value at (t-n) % (|m-n|).*/
    aiAnimBehaviour_REPEAT   = 0x3,

    /** This value is not used, it is just here to force the
     *  the compiler to map this enum to a 32 Bit integer  */
#ifndef SWIG
    _aiAnimBehaviour_Force32Bit = INT_MAX
#endif
};

// ---------------------------------------------------------------------------
/** Describes the animation of a single node. The name specifies the
 *  bone/node which is affected by this animation channel. The keyframes
 *  are given in three separate series of values, one each for position,
 *  rotation and scaling. The transformation matrix computed from these
 *  values replaces the node's original transformation matrix at a
 *  specific time.
 *  This means all keys are absolute and not relative to the bone default pose.
 *  The order in which the transformations are applied is
 *  - as usual - scaling, rotation, translation.
 *
 *  @note All keys are returned in their correct, chronological order.
 *  Duplicate keys don't pass the validation step. Most likely there
 *  will be no negative time values, but they are not forbidden also ( so
 *  implementations need to cope with them! )
�P��m�[�h�̃A�j���[�V�������L�q���܂��B���O�́A
 * ���̃A�j���[�V���� �`�����l���̉e�����󂯂�{�[��/�m�[�h�B�L�[�t���[��
 * �́A�ʒu�A
 *��]�ƃX�P�[�����O�B����炩��v�Z���ꂽ�ϊ��s��
 * �l�́A�m�[�h�̌��̕ϊ��s���
 *  ����̎��ԁB
 * ����́A���ׂẴL�[����ΓI�ł���A�{�[���̃f�t�H���g �|�[�Y�ɑ΂��đ��ΓI�ł͂Ȃ����Ƃ��Ӗ����܂��B
 * �ϊ����K�p����鏇���͎��̂Ƃ���ł��B
 * - �����̂悤�� - �X�P�[�����O�A��]�A�ړ��B
 *
 * @note ���ׂẴL�[�����������n�񏇂ɕԂ���܂��B
 * �d�������L�[�͌��؃X�e�b�v�ɍ��i���܂���B���Ԃ񂻂���
 * ���̎��Ԓl�͂���܂��񂪁A�֎~����Ă���킯�ł�����܂��� (
 * �����͂����ɑΏ�����K�v������܂�! )
 */
struct aiNodeAnim {
    /** ���̃A�j���[�V�����̉e�����󂯂�m�[�h�̖��O�B �m�[�h
      * ���݂���K�v������A��ӂł���K�v������܂��B*/
    C_STRUCT aiString mNodeName;

    /** �ʒu�L�[�̐� */
    unsigned int mNumPositionKeys;

    /** ���̃A�j���[�V���� �`�����l���̈ʒu�L�[�B �|�W�V������
       * 3D �x�N�g���Ƃ��Ďw��B �z��̃T�C�Y�� mNumPositionKeys �ł��B
       *
       * �ʒu�L�[������΁A���Ȃ��Ƃ� 1 ������܂�
       * �X�P�[�����O�� 1 �̉�]�L�[�B*/
    C_STRUCT aiVectorKey* mPositionKeys;

    /** ��]�L�[�̐� */
    unsigned int mNumRotationKeys;

    /** ���̃A�j���[�V���� �`�����l���̉�]�L�[�B ��]��
      * 4D �x�N�g���ł���N�H�[�^�j�I���Ƃ��ė^�����܂��B �z���
      * mNumRotationKeys �̃T�C�Y�B
      *
      *��]�L�[������΁A���Ȃ��Ƃ�1������܂�
      *�X�P�[�����O��1�̈ʒu�L�[�B */
    C_STRUCT aiQuatKey* mRotationKeys;

    /** The number of scaling keys */
    unsigned int mNumScalingKeys;

    /** ���̃A�j���[�V���� �`�����l���̃X�P�[�����O �L�[�B �X�P�[�����O��
        * 3D �x�N�g���Ƃ��Ďw��B �z��̃T�C�Y�� mNumScalingKeys �ł��B
        *
        * �X�P�[�����O �L�[������ꍇ�́A���Ȃ��Ƃ� 1 ������
        * �ʒu�� 1 �̉�]�L�[�B*/
    C_STRUCT aiVectorKey* mScalingKeys;

    /** �ŏ��̃A�j���[�V�����̑O�ɃA�j���[�V�������ǂ̂悤�ɓ��삷�邩���`���܂�
          * �L�[�ɑ������܂����B
          *
          ���f�t�H���g�l��aiAnimBehaviour_DEFAULT�i�I���W�i��
          * �e�����󂯂�m�[�h�̕ϊ��s�񂪎g�p����܂�)*/
    C_ENUM aiAnimBehaviour mPreState;

    /**�Ō�̃A�j���[�V�����̌�ɃA�j���[�V�������ǂ̂悤�ɓ��삷�邩���`���܂�
      * �L�[�͏�������܂����B
      *
      ���f�t�H���g�l��aiAnimBehaviour_DEFAULT�i�I���W�i��
      * �e�����󂯂�m�[�h�̕ϊ��s�񂪎擾����܂�)*/   
    C_ENUM aiAnimBehaviour mPostState;

#ifdef __cplusplus
    aiNodeAnim() AI_NO_EXCEPT
    : mNumPositionKeys( 0 )
    , mPositionKeys( nullptr )
    , mNumRotationKeys( 0 )
    , mRotationKeys( nullptr )
    , mNumScalingKeys( 0 )
    , mScalingKeys( nullptr )
    , mPreState( aiAnimBehaviour_DEFAULT )
    , mPostState( aiAnimBehaviour_DEFAULT ) {
         // empty
    }

    ~aiNodeAnim() {
        delete [] mPositionKeys;
        delete [] mRotationKeys;
        delete [] mScalingKeys;
    }
#endif // __cplusplus
};

// ---------------------------------------------------------------------------
/** Describes vertex-based animations for a single mesh or a group of
 *  meshes. Meshes carry the animation data for each frame in their
 *  aiMesh::mAnimMeshes array. The purpose of aiMeshAnim is to
 *  define keyframes linking each mesh attachment to a particular
 *  point in time. */
struct aiMeshAnim
{
    /** Name of the mesh to be animated. An empty string is not allowed,
     *  animated meshes need to be named (not necessarily uniquely,
     *  the name can basically serve as wild-card to select a group
     *  of meshes with similar animation setup)*/
    C_STRUCT aiString mName;

    /** Size of the #mKeys array. Must be 1, at least. */
    unsigned int mNumKeys;

    /** Key frames of the animation. May not be NULL. */
    C_STRUCT aiMeshKey* mKeys;

#ifdef __cplusplus

    aiMeshAnim() AI_NO_EXCEPT
        : mNumKeys()
        , mKeys()
    {}

    ~aiMeshAnim()
    {
        delete[] mKeys;
    }

#endif
};

// ---------------------------------------------------------------------------
/** Describes a morphing animation of a given mesh. */
struct aiMeshMorphAnim
{
    /** Name of the mesh to be animated. An empty string is not allowed,
     *  animated meshes need to be named (not necessarily uniquely,
     *  the name can basically serve as wildcard to select a group
     *  of meshes with similar animation setup)*/
    C_STRUCT aiString mName;

    /** Size of the #mKeys array. Must be 1, at least. */
    unsigned int mNumKeys;

    /** Key frames of the animation. May not be NULL. */
    C_STRUCT aiMeshMorphKey* mKeys;

#ifdef __cplusplus

    aiMeshMorphAnim() AI_NO_EXCEPT
        : mNumKeys()
        , mKeys()
    {}

    ~aiMeshMorphAnim()
    {
        delete[] mKeys;
    }

#endif
};

// ---------------------------------------------------------------------------
/** An animation consists of key-frame data for a number of nodes. For
 *  each node affected by the animation a separate series of data is given.*/
struct aiAnimation {
    /** The name of the animation. If the modeling package this data was
     *  exported from does support only a single animation channel, this
     *  name is usually empty (length is zero). */
    C_STRUCT aiString mName;

    /** �e�B�b�N�P�ʂ̃A�j���[�V�����̌p�����ԁB */
    double mDuration;

    /** 1 �b������̃e�B�b�N���B �C���|�[�g���ꂽ�t�@�C���Ŏw�肳��Ă��Ȃ��ꍇ�� 0 */ 
    double mTicksPerSecond;

    /** �{�[�� �A�j���[�V���� �`�����l���̐��B �e�`���l�����e�����܂�
        * �P��̃m�[�h�B */
    unsigned int mNumChannels;

    /** �m�[�h�̃A�j���[�V���� �`�����l���B �e�`���l���͒P��̃m�[�h�ɉe�����܂��B
        * �z��̃T�C�Y�� mNumChannels �ł��B */
    C_STRUCT aiNodeAnim** mChannels;


    /** ���b�V�� �A�j���[�V���� �`���l���̐��B �e�`���l�����e�����܂�
        * �P��̃��b�V���ł���A���_�x�[�X�̃A�j���[�V�������`���܂��B */
    unsigned int mNumMeshChannels;

    /** ���b�V�� �A�j���[�V���� �`�����l���B �e�`���l���͒P��̃��b�V���ɉe�����܂��B
        * �z��̃T�C�Y�� mNumMeshChannels �ł��B */
    C_STRUCT aiMeshAnim** mMeshChannels;

        /** ���b�V�� �A�j���[�V���� �`���l���̐��B �e�`���l�����e�����܂�
          * �P��̃��b�V���ŁA���[�t�B���O �A�j���[�V�������`���܂��B */
        unsigned int mNumMorphMeshChannels;

        /** ���[�t ���b�V�� �A�j���[�V���� �`�����l���B �e�`���l���͒P��̃��b�V���ɉe�����܂��B
            * �z��̃T�C�Y�� mNumMorphMeshChannels �ł��B */
        C_STRUCT aiMeshMorphAnim **mMorphMeshChannels;

#ifdef __cplusplus
    aiAnimation() AI_NO_EXCEPT
    : mDuration(-1.)
    , mTicksPerSecond(0.)
    , mNumChannels(0)
    , mChannels(nullptr)
    , mNumMeshChannels(0)
    , mMeshChannels(nullptr)
    , mNumMorphMeshChannels(0)
    , mMorphMeshChannels(nullptr) {
        // empty
    }

    ~aiAnimation() {
        // DO NOT REMOVE THIS ADDITIONAL CHECK
        if ( mNumChannels && mChannels )  {
            for( unsigned int a = 0; a < mNumChannels; a++) {
                delete mChannels[ a ];
            }

            delete [] mChannels;
        }
        if (mNumMeshChannels && mMeshChannels)  {
            for( unsigned int a = 0; a < mNumMeshChannels; a++) {
                delete mMeshChannels[a];
            }

            delete [] mMeshChannels;
        }
        if (mNumMorphMeshChannels && mMorphMeshChannels) {
                for( unsigned int a = 0; a < mNumMorphMeshChannels; a++) {
                        delete mMorphMeshChannels[a];
                }
            
            delete [] mMorphMeshChannels;
        }
    }
#endif // __cplusplus
};

#ifdef __cplusplus

}

/// @brief  Some C++ utilities for inter- and extrapolation
namespace Assimp {

// ---------------------------------------------------------------------------
/** 
  * @brief CPP-API: Utility class to simplify interpolations of various data types.
  *
  *  The type of interpolation is chosen automatically depending on the
  *  types of the arguments. 
  */
template <typename T>
struct Interpolator
{
    // ------------------------------------------------------------------
    /** @brief Get the result of the interpolation between a,b.
     *
     *  The interpolation algorithm depends on the type of the operands.
     *  aiQuaternion's and aiQuatKey's SLERP, the rest does a simple
     *  linear interpolation. */
    void operator () (T& out,const T& a, const T& b, ai_real d) const {
        out = a + (b-a)*d;
    }
}; // ! Interpolator <T>

//! @cond Never

template <>
struct Interpolator <aiQuaternion>  {
    void operator () (aiQuaternion& out,const aiQuaternion& a,
        const aiQuaternion& b, ai_real d) const
    {
        aiQuaternion::Interpolate(out,a,b,d);
    }
}; // ! Interpolator <aiQuaternion>

template <>
struct Interpolator <unsigned int>  {
    void operator () (unsigned int& out,unsigned int a,
        unsigned int b, ai_real d) const
    {
        out = d>0.5f ? b : a;
    }
}; // ! Interpolator <aiQuaternion>

template <>
struct Interpolator<aiVectorKey>  {
    void operator () (aiVector3D& out,const aiVectorKey& a,
        const aiVectorKey& b, ai_real d) const
    {
        Interpolator<aiVector3D> ipl;
        ipl(out,a.mValue,b.mValue,d);
    }
}; // ! Interpolator <aiVectorKey>

template <>
struct Interpolator<aiQuatKey>  {
    void operator () (aiQuaternion& out, const aiQuatKey& a,
        const aiQuatKey& b, ai_real d) const
    {
        Interpolator<aiQuaternion> ipl;
        ipl(out,a.mValue,b.mValue,d);
    }
}; // ! Interpolator <aiQuatKey>

template <>
struct Interpolator<aiMeshKey>     {
    void operator () (unsigned int& out, const aiMeshKey& a,
        const aiMeshKey& b, ai_real d) const
    {
        Interpolator<unsigned int> ipl;
        ipl(out,a.mValue,b.mValue,d);
    }
}; // ! Interpolator <aiQuatKey>

//! @endcond

} //  ! end namespace Assimp

#endif // __cplusplus

#endif // AI_ANIM_H_INC
