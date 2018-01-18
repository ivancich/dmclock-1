// -*- mode:C++; tab-width:8; c-basic-offset:2; indent-tabs-mode:t -*-
// vim: ts=8 sw=2 smarttab

/*
 * Copyright (C) 2017 Red Hat Inc.
 */


#pragma once


#include <ostream>
#include <assert.h>


namespace crimson {
  namespace dmclock {
    using Counter = uint64_t;

    enum class PhaseType : uint8_t { reservation, priority };

    inline std::ostream& operator<<(std::ostream& out, const PhaseType& phase) {
      out << (PhaseType::reservation == phase ? "reservation" : "priority");
      return out;
    }

    struct ReqParams {
      // count of all replies since last request; MUSTN'T BE 0
      uint64_t delta;

      // count of reservation replies since last request; MUSTN'T BE 0
      uint64_t rho;

      ReqParams(uint64_t _delta, uint64_t _rho) :
	delta(_delta),
	rho(_rho)
      {
	assert(rho <= delta);
      }

      ReqParams() :
	ReqParams(0, 0)
      {
	// empty
      }

      ReqParams(const ReqParams& other) :
	delta(other.delta),
	rho(other.rho)
      {
	// empty
      }

      friend std::ostream& operator<<(std::ostream& out, const ReqParams& rp) {
	out << "ReqParams{ delta:" << rp.delta <<
	  ", rho:" << rp.rho << " }";
	return out;
      }
    }; // class ReqParams
  }
}
