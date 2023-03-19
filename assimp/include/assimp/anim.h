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
全著作権所有。

ソースおよびバイナリ形式でのこのソフトウェアの再配布および使用、
変更の有無にかかわらず、次の条件で許可されます。
条件が満たされている:

* ソースコードの再配布は上記を保持する必要があります
  著作権表示、この条件リストおよび
  以下の免責事項。

* バイナリ形式での再配布は、上記を再現する必要があります
  著作権表示、この条件リストおよび
  ドキュメントおよび/またはその他の次の免責事項
  配布物とともに提供される資料。

* assimpチームの名前もその名前もありません
  寄稿者は、製品を推奨または宣伝するために使用される場合があります
  特定の事前確認なしに、このソフトウェアから派生した
  assimp チームの書面による許可。

このソフトウェアは、著作権所有者および貢献者によって提供されます
「現状のまま」および明示的または黙示的な保証を含みますが、そうではありません。
商品性および適合性の黙示の保証に限定されます。
特定の目的は否認されます。いかなる場合も、著作権を放棄しないものとします
所有者または貢献者は、直接的、間接的、付随的、
特別損害、懲罰的損害、結果的損害 (以下を含むが、
代替商品またはサービスの調達に限定されます。使用の損失、
データ、または利益;またはビジネスの中断) 原因の如何を問わず、
契約、厳格責任、または不法行為にかかわらず、責任の理論
(過失またはその他を含む) 使用から何らかの形で生じる
そのような損害の可能性について知らされていたとしても、このソフトウェアの
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
    
/** このキーの時刻 */
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
単一ノードのアニメーションを記述します。名前は、
 * このアニメーション チャンネルの影響を受けるボーン/ノード。キーフレーム
 * は、位置、
 *回転とスケーリング。これらから計算された変換行列
 * 値は、ノードの元の変換行列を
 *  特定の時間。
 * これは、すべてのキーが絶対的であり、ボーンのデフォルト ポーズに対して相対的ではないことを意味します。
 * 変換が適用される順序は次のとおりです。
 * - いつものように - スケーリング、回転、移動。
 *
 * @note すべてのキーが正しい時系列順に返されます。
 * 重複したキーは検証ステップに合格しません。たぶんそこに
 * 負の時間値はありませんが、禁止されているわけでもありません (
 * 実装はそれらに対処する必要があります! )
 */
struct aiNodeAnim {
    /** このアニメーションの影響を受けるノードの名前。 ノード
      * 存在する必要があり、一意である必要があります。*/
    C_STRUCT aiString mNodeName;

    /** 位置キーの数 */
    unsigned int mNumPositionKeys;

    /** このアニメーション チャンネルの位置キー。 ポジションは
       * 3D ベクトルとして指定。 配列のサイズは mNumPositionKeys です。
       *
       * 位置キーがあれば、少なくとも 1 つもあります
       * スケーリングと 1 つの回転キー。*/
    C_STRUCT aiVectorKey* mPositionKeys;

    /** 回転キーの数 */
    unsigned int mNumRotationKeys;

    /** このアニメーション チャンネルの回転キー。 回転は
      * 4D ベクトルであるクォータニオンとして与えられます。 配列は
      * mNumRotationKeys のサイズ。
      *
      *回転キーがあれば、少なくとも1つもあります
      *スケーリングと1つの位置キー。 */
    C_STRUCT aiQuatKey* mRotationKeys;

    /** The number of scaling keys */
    unsigned int mNumScalingKeys;

    /** このアニメーション チャンネルのスケーリング キー。 スケーリングは
        * 3D ベクトルとして指定。 配列のサイズは mNumScalingKeys です。
        *
        * スケーリング キーがある場合は、少なくとも 1 つもある
        * 位置と 1 つの回転キー。*/
    C_STRUCT aiVectorKey* mScalingKeys;

    /** 最初のアニメーションの前にアニメーションがどのように動作するかを定義します
          * キーに遭遇しました。
          *
          ※デフォルト値はaiAnimBehaviour_DEFAULT（オリジナル
          * 影響を受けるノードの変換行列が使用されます)*/
    C_ENUM aiAnimBehaviour mPreState;

    /**最後のアニメーションの後にアニメーションがどのように動作するかを定義します
      * キーは処理されました。
      *
      ※デフォルト値はaiAnimBehaviour_DEFAULT（オリジナル
      * 影響を受けるノードの変換行列が取得されます)*/   
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

    /** ティック単位のアニメーションの継続時間。 */
    double mDuration;

    /** 1 秒あたりのティック数。 インポートされたファイルで指定されていない場合は 0 */ 
    double mTicksPerSecond;

    /** ボーン アニメーション チャンネルの数。 各チャネルが影響します
        * 単一のノード。 */
    unsigned int mNumChannels;

    /** ノードのアニメーション チャンネル。 各チャネルは単一のノードに影響します。
        * 配列のサイズは mNumChannels です。 */
    C_STRUCT aiNodeAnim** mChannels;


    /** メッシュ アニメーション チャネルの数。 各チャネルが影響します
        * 単一のメッシュであり、頂点ベースのアニメーションを定義します。 */
    unsigned int mNumMeshChannels;

    /** メッシュ アニメーション チャンネル。 各チャネルは単一のメッシュに影響します。
        * 配列のサイズは mNumMeshChannels です。 */
    C_STRUCT aiMeshAnim** mMeshChannels;

        /** メッシュ アニメーション チャネルの数。 各チャネルが影響します
          * 単一のメッシュで、モーフィング アニメーションを定義します。 */
        unsigned int mNumMorphMeshChannels;

        /** モーフ メッシュ アニメーション チャンネル。 各チャネルは単一のメッシュに影響します。
            * 配列のサイズは mNumMorphMeshChannels です。 */
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
